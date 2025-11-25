#include <iostream>         // std::cout
#include <algorithm>        // std::sort
#include <iomanip>          // std::setprecision
#include <random>           // std::random_device, std::mt19937, std::bernoulli_distribution
#include <vector>           // std::vector
#include <string>           // std::string
#include <utility>          // std::pair
#include <numeric>          // std::iota
using std::vector;
using std::pair;
using std::string;
using std::cout;
using std::bernoulli_distribution;
using std::showpoint;
using std::fixed;
using std::setprecision;
using std::iota;
using std::sort;
using std::setfill;
using std::setw;

constexpr double AARON_SKILLS = 1.0/3.0;
constexpr double BOB_SKILLS = 0.5;
constexpr double CHARLIE_SKILLS = 1.0;

constexpr int GAMES = 10000;

std::random_device rd;
std::mt19937 rng(rd());

void gameStart(vector<pair<string, double> >& participants);
// Precondition: participants is empty
// Postcondition: participants contains the three players with their skills

void orderShoot(vector<pair<string, double> >& participants);
// Precondition: participants has at least two players
// Postcondition: participants is ordered by ascending skills

bool oneLeft(const vector<pair<string, double> >& participants);
// Postcondition: returns true if only one player is left

void gameRound(vector<pair<string, double> >& participants, bool bias);
// Precondition: participants has at least two players
// Postcondition: one round of shooting is done; if bias is true, Aaron
//                intentionally misses his first shot

void addStats(const vector<pair<string, double> >& participants,
              vector<pair<string, int> >& winStats);
// Precondition: participants has only one player (the winner)
// Postcondition: winStats is updated with the winner's stats

void showStats(const vector<pair<string, int> >& winStats, bool bias);
// Postcondition: winStats is displayed; if bias is true, indicates that
//                Aaron intentionally missed his first shot

void eraseStats(vector<pair<string, int> >& vectorPlayers);
// Postcondition: vectorPlayers is cleared
//               (not used in this implementation, but could be useful)

int main( ) {
    cout << fixed << showpoint << setprecision(2);
    vector<pair<string, double> > participants;
    vector<pair<string, int> > winStats;
    vector<pair<string, int> > winStatsBiased;

    // Strategy 1: Aaron hits at first shot
    for (int game = 0; game < GAMES; ++game ) {
        gameStart(participants);
        while (!oneLeft(participants)) {
            gameRound(participants, false);
        }
        addStats(participants, winStats);
    }
    showStats(winStats, false);

    // Strategy 2: Aaron intentionally misses first shot
    for (int game = 0; game < GAMES; ++game ) {
        gameStart(participants);

        size_t initial_size = participants.size();
        while (initial_size == participants.size())
            gameRound(participants, true);
        while (!oneLeft(participants)) {
            gameRound(participants, false);
        }
        addStats(participants, winStatsBiased);
    }
    showStats(winStatsBiased, true);



    cout << "\n";
    return 0;
}


void gameStart(vector<pair<string, double> >& participants) {
    // clean list each game
    participants.clear();
    participants.emplace_back("Aaron", AARON_SKILLS);
    participants.emplace_back("Bob", BOB_SKILLS);
    participants.emplace_back("Charlie", CHARLIE_SKILLS);
    orderShoot(participants);
}

void orderShoot(vector<pair<string, double> >& participants) {
    if (participants.size() < 2) return;

    for (size_t idx1 = 0; idx1 < participants.size() - 1; ++idx1) {

        size_t bestShooterId = idx1;
        double bestShooterStats = participants[idx1].second;

        for (size_t idx2 = idx1 + 1; idx2 < participants.size(); ++idx2) {
            if (participants[idx2].second < bestShooterStats) {
                bestShooterId = idx2;
                bestShooterStats =  participants[idx2].second;
            }
        }
        if (bestShooterId != idx1)
            participants[idx1].swap(participants[bestShooterId]);
    }
}

bool oneLeft(const vector<pair<string, double> >& participants) {
    return (participants.size() == 1);
}

void gameRound(vector<pair<string, double> >& participants, const bool bias) {
    if (participants.size() < 2) return;

    // set starting player depending on Aaron missing (biased) or hitting
    size_t nPlayer = (bias == true) ? 1 : 0;

    while (nPlayer < participants.size()) {
        bernoulli_distribution hit(participants[nPlayer].second);
        if (!hit(rng)) {
            // missed shot
            ++nPlayer;
            continue;
        }

        // Players shoot in order of skills (ascending).
        // Kill the most lethal (last) then second to last, etc.
        const size_t mostLethal = participants.size() - 1;
        const size_t target = (nPlayer == mostLethal) ? nPlayer - 1 : mostLethal;

        // most lethal is shot
        using diff_t = vector<pair<string, double>>::difference_type;
        participants.erase(participants.begin() + static_cast<diff_t>(target));

        if (bias)       // if Aaron doesn't shoot at first (bias),
            return;     // he starts when one participant dies

        // if we removed element before current shooter,
        // current shooter's index decreased by 1
        if (target < nPlayer) --nPlayer;

        if (participants.size() < 2) break;

        ++nPlayer;
    }
}


void addStats(const vector<pair<string, double> >& participants, vector<pair<string, int> >& winStats) {
    if (participants.empty()) return;

    const string& winner = participants.front().first;

    for (auto& entry : winStats)
        if (entry.first == winner) {
            ++entry.second;
            return;
        }

    winStats.emplace_back(winner, 1);
}

void showStats(const vector<pair<string, int> >& winStats, const bool bias) {
    // avoid copying strings, but sort the indices only

    vector<size_t> indices(winStats.size());
    iota(indices.begin(), indices.end(), 0);

    sort(indices.begin(), indices.end(),
        [&](const size_t pair1, const size_t pair2) {
            return (winStats[pair1].first < winStats[pair2].first);
            });
    if (bias)
        cout << setfill('-') << setw(50) << "" << setfill(' ') << "\n"
             << "Biased game (Aaron misses intentionally first)\n";

    for (size_t idx : indices) {
        double stats = static_cast<double>(winStats[idx].second) / GAMES;
        cout << winStats[idx].first << " won "
             << winStats[idx].second << "/"
             << GAMES << " duels or "
             << stats * 100.0 << "%\n";
    }
}

void eraseStats(vector<pair<string, int> >& vectorPlayers) {
    vectorPlayers = vector<pair<string, int> >();
}
