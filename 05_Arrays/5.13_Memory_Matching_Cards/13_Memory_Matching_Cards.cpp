#include <iostream>
#include <random>
#include <sstream>

constexpr int ROWS = 4;
constexpr int COLS = 4;
constexpr int CARDS = ROWS * COLS;
constexpr int SAME = 2;
constexpr int COORDINATES = 2;
constexpr char UNFOLD = '*';
constexpr char FOLD = '#';

void createBoard(int cards[][COLS], char upDown[][COLS], int nRows);
//   Precondition: nRows is the number of rows in cards and upDown.
// cards is an array of size nRows x COLS that will hold the card values.
// upDown is an array of size nRows x COLS that will hold the card face status.
//   Postcondition: cards[0][0] through cards[nRows-1][COL-1]
// have been initialized with pairs of values from 1 to CARDS/2.
// upDown[0][0] through upDown[nRows-1][COL-1] have been initialized to UNFOLD.

void shuffleCards(int cards[][COLS], int nRows);
//   Precondition: nRows is the number of rows in cards.
// cards is an array of size nRows x COLS that holds the card values.
//   Postcondition: the elements of cards have been randomly shuffled.

void showBoard(const int cards[][COLS], const char upDown[][COLS], int nRows);
//   Precondition: nRows is the number of rows in cards and upDown.
// cards is an array of size nRows x COLS that holds the card values.
// upDown is an array of size nRows x COLS that holds the card face status.
//   Postcondition: the contents of cards have been displayed on the console,
// showing UNFOLD for facedown cards and the card value for faceup cards.

bool chooseCards(int nRows, int nCols, int card1[], int card2[], int dimensions);
//   Precondition: nRows is the number of rows in the board, nCols is the number of columns in the board.
// card1 and card2 are arrays of size 2 that will hold the row and column of the chosen cards.
// dimensions is the number of cards to choose (2 in this case).
//   Postcondition: the user has been prompted to enter the coordinates of two cards.
// The function returns true if the user successfully chose two cards, or false
// if the user decided to exit the game.

void unfold(const int cards[][COLS], char upDown[][COLS], int nRows,
            const int card1[], const int card2[], int dimensions, int& remainingCards);
//   Precondition: nRows is the number of rows in cards and upDown.
// cards is an array of size nRows x COLS that holds the card values.
// upDown is an array of size nRows x COLS that holds the card face status.
// card1 and card2 are arrays of size 2 that hold the row and column of the chosen cards.
// dimensions is the number of cards chosen (2 in this case).
// remainingCards is the number of unmatched cards remaining in the game.
//   Postcondition: the chosen cards have been unfolded (faceup). If the cards match,
// they remain faceup; otherwise, they are turned facedown again.

void clearConsole();
//   Postcondition: the console output has been cleared by printing multiple newlines.

int main( ) {
    int board[ROWS][COLS] = {0};
    char upDown[ROWS][COLS];
    int card1[2], card2[2];
    int unmatchedCards = CARDS;
    createBoard(board, upDown, ROWS);
    shuffleCards(board, ROWS);
    showBoard(board, upDown, ROWS);

    while (chooseCards(ROWS, COLS, card1, card2, COORDINATES) && unmatchedCards > 0) {
        unfold(board, upDown, ROWS, card1, card2, COORDINATES, unmatchedCards);
        showBoard(board, upDown, ROWS);
    }
    if (unmatchedCards == 0) std::cout << "You won!\n";
    else                     std::cout << "Game over\n";

    std::cout << "\n";
    return 0;
}

void createBoard(int cards[][COLS], char upDown[][COLS], const int nRows) {
    int cardValue = 1;
    for (int row = 0; row < nRows; ++row)
        for (int col = 0; col < COLS; col++) {
            if (col % SAME == 0)
                cards[row][col] = cardValue;
            else
                cards[row][col] = cardValue++;
            upDown[row][col] = UNFOLD;
        }
}

void shuffleCards(int cards[][COLS], int nRows) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    const int total = nRows * COLS;
    // Fisher-Yates on flattened indices
    for (int card = total - 1; card > 0; --card) {
        std::uniform_int_distribution<int>dist(0, card);
        const int randomCard = dist(gen);
        const int rowRandomCard = randomCard / COLS;
        const int colRandomCard = randomCard % COLS;
        const int rowCard = card / COLS;
        const int colCard = card % COLS;
        std::swap(cards[rowCard][colCard],
                  cards[rowRandomCard][colRandomCard]);
    }
}

void showBoard(const int cards[][COLS], const char upDown[][COLS], int nRows) {
    // Print header
    std::cout << "   ";
    for (int col = 0; col < COLS; ++col)
        std::cout << (col + 1) << " ";
    std::cout << "\n";
    std::cout << "   ";
    for (int col = 0; col < COLS; ++col)
        std::cout << "--";
    std::cout << "\n";


    for (int row = 0; row < nRows; ++row) {
        std::cout << (row + 1);
        std::cout << " |";
        for (int col = 0; col < COLS; ++col) {
            if (upDown[row][col] == UNFOLD)  std::cout << UNFOLD << " ";
            else                           std::cout << cards[row][col] << " ";
        }
        std::cout << "\n";
    }

    // Show true values. DEBUG ONLY
    // for (int row = 0; row < nRows; ++row) {
    //     for (int col = 0; col < COLS; ++col)
    //         std::cout << cards[row][col] << " ";
    //     std::cout << "\n";
    // }
}

bool chooseCards(const int nRows, const int nCols, int card1[], int card2[], const int dimensions) {
    std::string line;
    for (int pick = 1; pick <= dimensions; ++pick) {
        while (true) {
            std::cout << "Enter row and column of card " << pick
                      << " (1.." << nRows << " 1.." << nCols << ")\n"
                      << "(Or type `exit` to end the program)\n";
            // EOF or input error
            if (!std::getline(std::cin,line)) {
                std::cout << "End of input\n";
                return false;
            }
            if (line == "exit")
                return false;

            std::istringstream iss(line);
            int row, col;
            if (!(iss >> row >> col)) {
                std::cout << "Invalid input. Retry\n";
                continue;
            }
            --row;
            --col;
            if (row < 0 || row >= nRows || col < 0 || col >= nCols) {
                std::cout << "No valid card selected. Retry\n";
                continue;
            }
            // do not pick the same card
            if (pick == 2 && row == card1[0] && col == card1[1]) {
                std::cout << "Choose a different card.\n";
                continue;
            }
            switch (pick) {
                case 1:
                    card1[0] = row;
                    card1[1] = col;
                    break;
                case 2:
                    card2[0] = row;
                    card2[1] = col;
                    break;
                default:
                    break;
            }
            break;
        }
    }
    return true;
}

void unfold(const int cards[][COLS], char upDown[][COLS], const int nRows,
            const int card1[], const int card2[], const int dimensions, int& remainingCards) {

    const int rowCard1 = card1[0], colCard1 = card1[1];
    const int rowCard2 = card2[0], colCard2 = card2[1];

    bool card1seen = false, card2seen = false;
    if (upDown[rowCard1][colCard1] == FOLD) card1seen = true;
    if (upDown[rowCard2][colCard2] == FOLD) card2seen = true;



    upDown[rowCard1][colCard1] = FOLD;
    upDown[rowCard2][colCard2] = FOLD;
    if (cards[rowCard1][colCard1] == cards[rowCard2][colCard2]) {
        remainingCards -= 2;
        std::cout << "Found a match!\n";
        return;
    }
    // for unpaired match, show and then hide pair
    showBoard(cards, upDown, nRows);
    std::cout << "Cards do not match. Press `Enter` to continue\n";
    std::string keystroke;
    std::getline(std::cin, keystroke);
    if (!card1seen)
        upDown[rowCard1][colCard1] = UNFOLD;
    if (!card2seen)
        upDown[rowCard2][colCard2] = UNFOLD;

    clearConsole();
}

void clearConsole() {
    for (int idx = 0; idx < 8; ++idx) std::cout << "\n";
}
