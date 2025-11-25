#include <iostream>
#include <random>
#include <limits>

constexpr int PLAYERS = 2;
constexpr int N_ROWS = 3;
constexpr int N_COLS = 3;
constexpr int MOVES = 5;

enum class PlayerIndex { O = 0, X = -1};

int boardValue(PlayerIndex player);
//   Precondition: player is either PlayerIndex::O or PlayerIndex::X
//   Postcondition: returns an integer (-1 for Player X and 0 for Player O)

char playerChar(PlayerIndex player);
//   Precondition: player is either PlayerIndex::O or PlayerIndex::X
//   Postcondition: returns 'X' for Player X and '0' for Player O

void togglePlayer(PlayerIndex& player);
//   Precondition: player is either PlayerIndex::O or PlayerIndex::X
//   Postcondition: player is toggled to the other player

void initializeBoard(int board[][N_COLS], int nRows);
//   Precondition: nRows is the number of rows in the board
//   Postcondition: board is initialized with position numbers from 1 to nRows * N_COLS

void showBoard(const int board[][N_COLS], int nRows);
//   Precondition: nRows is the number of rows in the board
//   Postcondition: displays the current state of the board
// (cells occupied by players are shown as 'X' or '0', others as position numbers)

void playTurn(int board[][N_COLS], int nRows,
              int movesPlayer[], int& nMoves,
              PlayerIndex playerNumber);
//   Precondition: nRows is the number of rows in the board
// movesPlayer is an array to store the moves of the current player
// nMoves is the number of moves made by the current player
// playerNumber is either PlayerIndex::O or PlayerIndex::X
//   Postcondition: prompts the player to enter a valid move
// (number corresponding to an unoccupied cell),
// updates the board and records the move

int enterMove(const int board[][N_COLS], int nRows, PlayerIndex playerNumber);
//   Precondition: nRows is the number of rows in the board
// playerNumber is either PlayerIndex::O or PlayerIndex::X
//   Postcondition: prompts the player to enter a valid move
// (number corresponding to an unoccupied cell), and returns that move

bool isCellBusy(const int board[][N_COLS], int nRows, int position);
//   Precondition: nRows is the number of rows in the board
// position is the cell number to check
//   Postcondition: returns true if the cell at the given position
// is already occupied by a player; false otherwise

int main( ) {
    int board[N_ROWS][N_COLS];
    int placesLeft = N_ROWS * N_COLS;
    int movesPlayerX[MOVES] = {};
    int nMovesX = 0;
    int movesPlayerO[MOVES] = {};
    int nMovesY = 0;

    std::mt19937 rng(std::random_device{}());       // random number generator
    std::uniform_int_distribution<int> playerNumber(0, 1);
    PlayerIndex playerTurn = (playerNumber(rng) == 0) ? PlayerIndex::O : PlayerIndex::X;

    initializeBoard(board, N_ROWS);
    while (placesLeft > 0) {

        if (playerTurn == PlayerIndex::O)
            playTurn(board, N_ROWS, movesPlayerO, nMovesY, playerTurn);
        else if (playerTurn == PlayerIndex::X)
            playTurn(board, N_ROWS, movesPlayerX, nMovesX, playerTurn);

        togglePlayer(playerTurn);
        --placesLeft;
    }

    showBoard(board, N_ROWS);

    std::cout << "\n";
    return 0;
}

int boardValue(const PlayerIndex player) {
    return static_cast<int>(player);
}

char playerChar(const PlayerIndex player) {
    switch (player) {
        case PlayerIndex::O: return '0';
        case PlayerIndex::X: return 'X';
        default: return '?';
    }
}


void initializeBoard(int board[][N_COLS], const int nRows) {
    int num = 0;
    for (int row = 0; row < nRows; ++row)
        for (int col = 0; col < N_COLS; ++col)
            board[row][col] = ++num;
}

void playTurn(int board[][N_COLS], const int nRows,
              int movesPlayer[], int& nMoves,
              const PlayerIndex playerNumber) {

    int movePlace = enterMove(board, nRows, playerNumber);
    movesPlayer[nMoves++] = movePlace;
    int row = (movePlace - 1) / N_COLS;
    int col = (movePlace - 1) % N_COLS;
    board[row][col] = boardValue(playerNumber);
}

int enterMove(const int board[][N_COLS], const int nRows, const PlayerIndex playerNumber) {
    int next;
    while (true) {
        showBoard(board, nRows);
        std::cout << "Player " << playerChar(playerNumber) << ", enter a valid move:\n";
        if (!(std::cin >> next)) {
            std::cout << "Not a number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // consume remaining input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // check position in the grid
        if ((next < 1) || (next > nRows * N_COLS)) {
            std::cout << "Not a valid position\n";
            continue;
        }

        if (isCellBusy(board, nRows, next)) {
            std::cout << "Position already chosen. Retry\n";
            continue;
        }

        return next;
    }
}

void showBoard(const int board[][N_COLS], const int nRows) {

    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < N_COLS; ++col) {
            int cell = board[row][col];

            if (cell == boardValue(PlayerIndex::O))
                std::cout << playerChar(PlayerIndex::O) << " ";

            else if (cell == boardValue(PlayerIndex::X))
                std::cout << playerChar(PlayerIndex::X) << " ";

            else  std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void togglePlayer(PlayerIndex& player) {
    player = (player == PlayerIndex::O) ? PlayerIndex::X : PlayerIndex::O;
}

bool isCellBusy(const int board[][N_COLS], const int nRows, const int position) {
    int row = (position - 1) / N_COLS;
    int col = (position - 1) % N_COLS;
    return (board[row][col] < 1);
}
