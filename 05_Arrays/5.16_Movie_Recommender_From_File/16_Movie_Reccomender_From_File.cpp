#include <fstream>      // for std::fstream
#include <sstream>      // for std::istringstream
#include <algorithm>    // for std::min_element
#include <iostream>     // for std::cout, std::cin, std::cerr
#include <cstring>      // for std::memcpy
#include <limits>       // for std::numeric_limits
#include <cmath>        // for std::fabs
#include <iomanip>      // for std::setprecision, std::fixed, std::showpoint

const std::string PATH = "./05_Arrays/5.16_Movie_Recommender_From_File/Utilities/ratings.txt";
constexpr int MAX_REVIEWERS = 1000;
constexpr int MOVIES = 6;
constexpr int CHOICES = 3;
constexpr int FIRST = 100;
constexpr int LAST = 100 + MOVIES - 1;
constexpr double MIN = 1.0;
constexpr double MAX = 5.0;

void copyData(const std::string& path, int reviews[][MOVIES], int& people);
//   Precondition: path is a valid file path
//   Postcondition: reads the file and fills reviews with the movie ratings from users.

bool openFile(const std::string& path, std::fstream& inputStream);
//   Precondition: path is a valid file path
//   Postcondition: opens the file located at path for reading.

void closeFile(const std::string& path, std::fstream& inputStream);
//   Precondition: path is a valid file path
//   Postcondition: closes the file located at path.

void fillReviews(int reviews[][MOVIES], int reviewers);
//   Precondition: reviewers is the declared size of the first dimension of reviews.
//   Postcondition: reviews[0] through reviews[reviewers - 1] have been filled
// with the movie ratings from users.

void makeChoice(int choices[], double scoreChoice[], int nMovies, int notSeen[], int notSeenMovies);
//   Precondition: nMovies is the total number of movies.
//   Postcondition: choices[0] through choices[nMovies - 1] have been filled
// with the movie codes chosen by the user, and scoreChoice[0] through scoreChoice[nMovies - 1]
// have been filled with the corresponding ratings.
// notSeen[0] through notSeen[notSeenMovies - 1] have been filled with the movie codes
// not chosen by the user. notSeenMovies = nMovies - number of choices.

void addNotChosen(int notSeen[], int notSeenMovies, const int choices[], int nMovies);
//   Precondition: nMovies is the total number of movies.
//   Postcondition: notSeen[0] through notSeen[notSeenMovies - 1] have been filled
// with the movie codes not chosen by the user.

bool movieAlreadyChosen(const int choices[], int nChoices, int code);
//   Precondition: nChoices is the number of choices already made.
//   Postcondition: returns true if code is already in choices[0] through choices[nChoices - 1],
// otherwise returns false.

bool correctInput(int code, double score);
//   Postcondition: returns true if code is between FIRST and LAST (inclusive)
// and score is between MIN and MAX (inclusive), otherwise returns false.

void predictScore(const int reviews[][MOVIES], int reviewers,
                  const int choices[], const double scoreChoice[], int nChoices,
                  const int notSeen[], double ratingNotSeen[], int notSeenSize);
//   Precondition: reviewers is the declared size of the first dimension of reviews.
//   Postcondition: ratingNotSeen[0] through ratingNotSeen[notSeenSize - 1]
// have been filled with the predicted ratings for the movies in notSeen[0]
// through notSeen[notSeenSize - 1].

void computeDistance(const int choices[], const double scoreChoice[], int nChoices,
                     const int reviews[][MOVIES], double distance[], int nReviewers);
// Helper to `predictScore`
//   Precondition: nChoices is the number of choices made by the user.
//   Postcondition: distance[0] through distance[nReviewers - 1]
// have been filled with the computed distances between the user's choices
// and each reviewer's ratings.

bool findMostSimilar(const double distance[], int similarRatingReviewers[], int nReviewers, int& nSimilar);
// Helper to `predictScore`
//   Precondition: nReviewers is the declared size of distance.
//   Postcondition: similarRatingReviewers[0] through similarRatingReviewers[nSimilar - 1]
// have been filled with the indices of the reviewers with the smallest distance.
// nSimilar is set to the number of similar reviewers found.

void computeRatingFromSimilar(const int notSeen[], double ratingNotSeen[], int notSeenSize,
                              const int similarRatingReviewers[], int sizeSimilar,
                              const int reviews[][MOVIES], int totReviewers);
// Helper to `predictScore`
//   Precondition: sizeSimilar is the number of similar reviewers found.
//   Postcondition: ratingNotSeen[0] through ratingNotSeen[notSeenSize - 1]
// have been filled with the average ratings from the similar reviewers
// for the movies in notSeen[0] through notSeen[notSeenSize - 1].

void showSimilar(const int similarRatingReviewers[], int sizeSimilar,
                 const double distance[], int totReviewers);
// Helper to `predictScore`
//   Precondition: sizeSimilar is the number of similar reviewers found.
//   Postcondition: displays on console the similar reviewers and their distances.

void showPrediction(const int notSeen[], const double ratingNotSeen[], int notSeenSize);
//   Precondition: notSeenSize is the size of notSeen and ratingNotSeen.
//   Postcondition: displays on console the predicted ratings for the movies
// in notSeen[0] through notSeen[notSeenSize - 1].

void showReviews(const int reviews[][MOVIES], int reviewers);
//   Precondition: reviewers is the declared size of the first dimension of reviews.
//   Postcondition: displays on console the reviews table.

int main( ) {
    int people = 0;
    int reviews[MAX_REVIEWERS][MOVIES];
    int choices[CHOICES] = {-1, -1, -1};
    double scoreChoice[CHOICES] = {0.0};
    int notSeen[MOVIES - CHOICES];
    double ratingNotSeen[MOVIES - CHOICES] = {0.0};

    copyData(PATH, reviews, people);
    if (people == 0) {
        std::cerr << "No reviewers, exiting\n";
        return -1;
    }
    showReviews(reviews, people);
    makeChoice(choices, scoreChoice, CHOICES, notSeen, MOVIES - CHOICES);
    predictScore(reviews, people, choices, scoreChoice, CHOICES, notSeen, ratingNotSeen, MOVIES - CHOICES);
    showPrediction(notSeen, ratingNotSeen, MOVIES - CHOICES);

    std::cout << "\n";
    return 0;
}

void makeChoice(int choices[], double scoreChoice[], const int nMovies,
                int notSeen[], const int notSeenMovies) {
    int code;
    double score;
    for (int movie = 0; movie < nMovies; ++movie) {
        std::cout << "Enter the movie and rating (1.0-5.0)\n";
        while (true) {
            if (!(std::cin >> code >> score)) {
                std::cout << "Wrong input. Retry\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if (movieAlreadyChosen(choices, movie, code)) continue;
            if (correctInput(code, score)) {
                choices[movie] = code;
                scoreChoice[movie] = score;
                break;
            }
            std::cout << "Wrong values. Retry\n";
        }
    }
    addNotChosen(notSeen, notSeenMovies, choices, nMovies);
}

void addNotChosen(int notSeen[], const int notSeenMovies,
                  const int choices[], const int nMovies) {

    int idxNotSeen = 0;
    for (int movie = FIRST; movie <= LAST && idxNotSeen < notSeenMovies; ++movie) {
        bool chosen = false;

        for (int choice = 0; choice < nMovies; ++choice) {
            if (movie == choices[choice]) {
                chosen = true;
                break;
            }
        }
        if (!chosen) notSeen[idxNotSeen++] = movie;
    }
}

bool movieAlreadyChosen(const int choices[], const int nChoices, const int code) {
    for (int idx = 0; idx < nChoices; ++idx)
        if (choices[idx] == code) {
            std::cout << "Movie already rated. Retry\n";
            return true;
        }
    return false;
}

bool correctInput(const int code, const double score) {
    return ((code >= FIRST) && (code <= LAST) &&
                (score >= MIN) && (score <= MAX));
}

void predictScore(const int reviews[][MOVIES], const int reviewers,
                  const int choices[], const double scoreChoice[], const int nChoices,
                  const int notSeen[], double ratingNotSeen[], const int notSeenSize) {

    if (reviewers <= 0) {
        std::cout << "No reviewers available.\n";
        return;
    }

    double distance[MAX_REVIEWERS] = {0.0};
    int similarRatingReviewers[MAX_REVIEWERS];
    int sizeSimilar = 0;
    computeDistance(choices, scoreChoice, nChoices, reviews, distance, reviewers);
    if (!findMostSimilar(distance, similarRatingReviewers, reviewers, sizeSimilar)) {
        std::cerr << "No similar reviewers found\n";
        return;
    }
    computeRatingFromSimilar(notSeen, ratingNotSeen, notSeenSize,
                             similarRatingReviewers, sizeSimilar,
                             reviews, reviewers);
    showSimilar(similarRatingReviewers, sizeSimilar, distance, reviewers);
}

void computeDistance(const int choices[], const double scoreChoice[], const int nChoices,
                     const int reviews[][MOVIES], double distance[], const int nReviewers) {

    // distance for each movie chosen
    for (int choice = 0; choice < nChoices; ++choice) {
        const int codeChoice = choices[choice] - FIRST;
        // consider every reviewer
        for (int reviewer = 0; reviewer < nReviewers; ++reviewer) {
            const double difference = scoreChoice[choice] - reviews[reviewer][codeChoice];
            distance[reviewer] += difference * difference;
        }
    }
}

bool findMostSimilar(const double distance[], int similarRatingReviewers[], const int nReviewers, int& nSimilar) {
    nSimilar = 0;
    const double min = *std::min_element(distance, distance + nReviewers);
    constexpr double EPS = 1e-9;
    for (int reviewer = 0; reviewer < nReviewers; ++reviewer)
        if (std::fabs(distance[reviewer] - min) <  EPS)
            similarRatingReviewers[nSimilar++] = reviewer;

    if (nSimilar == 0)
        return false;
    return true;
}

void computeRatingFromSimilar(const int notSeen[], double ratingNotSeen[], const int notSeenSize,
                              const int similarRatingReviewers[], const int sizeSimilar,
                              const int reviews[][MOVIES], const int totReviewers) {

    for (int notSeenMovie = 0; notSeenMovie < notSeenSize; ++notSeenMovie) {
        double sum = 0.0;
        const int movieCode = notSeen[notSeenMovie];
        const int movieIdx = movieCode - FIRST;
        for (int similarPerson = 0; similarPerson < sizeSimilar; ++similarPerson) {
            const int reviewer = similarRatingReviewers[similarPerson];
            sum += reviews[reviewer][movieIdx];
        }

        ratingNotSeen[notSeenMovie] = sum / static_cast<double>(sizeSimilar);
    }

}

void showSimilar(const int similarRatingReviewers[], const int sizeSimilar,
                 const double distance[], const int totReviewers) {

    std::cout << "Most similar reviewers:\n";
    for (int idx = 0; idx < sizeSimilar; ++idx) {
        const int person = similarRatingReviewers[idx];
        std::cout << similarRatingReviewers[idx] << ", distance: " << distance[person] << "\n";
    }
}



void showPrediction(const int notSeen[], const double ratingNotSeen[], const int notSeenSize) {
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    for (int idx = 0; idx < notSeenSize; ++idx)
        std::cout << "Movie " << notSeen[idx]
                  << ", Predicted Rating: " << ratingNotSeen[idx] << "\n";
}

void showReviews(const int reviews[][MOVIES], const int reviewers) {
    // Print header
    std::cout << "Movie: ";
    for (int col = FIRST; col <= LAST; ++col)
        std::cout << col << " ";
    std::cout << "\n";
    std::cout << "User ";
    for (int col = FIRST; col <= LAST; ++col)
        std::cout << "----";
    std::cout << "\n";


    for (int reviewer = 0; reviewer < reviewers; ++reviewer) {
        std::cout << "#" << reviewer;
        std::cout << "  |   ";
        for (int movie = 0; movie < MOVIES; ++movie)
            std::cout << reviews[reviewer][movie] << "   ";
        std::cout << "\n";
    }

}

void copyData(const std::string& path, int reviews[][MOVIES], int& people) {
    std::fstream inputStream;
    if (!openFile(path, inputStream)) {
        std::cerr << "Cannot open file\n";
        people = 0;
        return;
    }
    std::string line;
    int user = 0;

    std::getline(inputStream, line);             // skip header
    while (std::getline(inputStream, line)) {
        if (line.empty())   continue;
        if (user >= MAX_REVIEWERS)  break;

        std::istringstream iss(line);
        int read[MOVIES + 1] = {0};     // read[0]: user0 rate100 rate101 ... rate 105
        int number, field = 0;
        while (field < (1 + MOVIES) && (iss >> number)) // 1 user + MOVIES
            read[field++] = number;

        if (field < (1 + MOVIES))  continue;            // skip if not all fields
        for (int idx = 0; idx < MOVIES; ++idx) {
            int movie = idx + 1;
            reviews[user][idx] = read[movie];
        }
        ++user;
    }
    people = user;
    closeFile(path, inputStream);
}

bool openFile(const std::string& path, std::fstream& inputStream) {
    inputStream.open(path);
    if (!inputStream)
        return false;
    return true;
}

void closeFile(const std::string& path, std::fstream& inputStream) {
    inputStream.close();
}
