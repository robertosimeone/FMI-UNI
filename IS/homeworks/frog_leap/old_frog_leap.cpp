#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;
std::vector<std::vector<char> > availableBoards_generate(std::vector<char>& board) {
    int emptyIndex = 0;
    while (board[emptyIndex] != '_') {
        emptyIndex++;
    }
    std::vector<int> possibleMoves;
    for (int x = -2; x <= 2; x++) {
        int addend = emptyIndex + x;
        if (addend >= 0 && addend < board.size() && x != 0) {
            possibleMoves.push_back(addend);
        }
    }

    std::vector<std::vector<char> > possibleBoards;
    for (int addend : possibleMoves) {
        if ((addend < emptyIndex && board[addend] == '>') || (addend > emptyIndex && board[addend] == '<')) {
            std::vector<char> newBoard = board;
            std::swap(newBoard[addend], newBoard[emptyIndex]);
            possibleBoards.push_back(newBoard);
        }
    }
    return possibleBoards;
}
bool isSolved(std::vector<char>& board) {
    int n = (board.size() - 1) / 2;
    int emptyIndex = n;
    if (board[emptyIndex] != '_') {
        return false;
    }
    for (int i = 0; i < n; i++) {
        if (board[i] != '<') {
            return false;
        }
    }
    return true;
}

bool frogLeap(std::vector<char>& board, int emptyIndex, std::vector<std::vector<char> >& stack) {
    if (isSolved(board)) {
        return true;
    }
    std::vector<std::vector<char> > availableBoards = availableBoards_generate(board);
    for ( auto& _board : availableBoards) {
        if (frogLeap(_board,emptyIndex, stack)) {
            stack.push_back(_board);
            return true;
        }
    }
    return false;
}


void frogLeapCalculation(int n) {
    std::vector<char> board;
    for (int i = 0; i < n; i++) {
        board.push_back('>');
    }
    board.push_back('_');
    for (int i = 0; i < n; i++) {
        board.push_back('<');
    }
    std::vector<std::vector<char> > stack;
    std::clock_t start = std::clock();
    frogLeap(board, n, stack);
    std::clock_t end = std::clock();
    double elapsedSeconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << elapsedSeconds << " seconds" << std::endl;
    std::cout << stack.size() << std::endl;
//    std::cout << "RL_RR" << std::endl;
    for (int i = stack.size() - 1; i >= 0; i--) {
        const auto& currentBoard = stack[i];
        for (char c : currentBoard) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

int main() {
    int n;
    std::cin >> n;
    frogLeapCalculation(n);
    return 0;
    //5 6 3 4 8 0 1 15 10 7 2 11
}
