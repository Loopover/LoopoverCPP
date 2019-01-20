#include "boardhashing.hpp"

template <int N>
void _flatten(const Board<N> &board, std::vector<int> &result) {
    result.clear();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result.push_back(board.tiles[i][j]);
        }
    }
}

template <int N>
void _deflatten(const vector<int> &result, Board<N> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = result[N*i+j];
        }
    }
}

// Board to BigInt hashing done in O(N^2 log^2 N) time, where N is board size.
//
// Btw, the log^2 N comes from BigInt multiplication
//
// If integer arithmetic always took constant time, we would have O(N^2 log N)
template <int N>
void board_hash(const Board<N> &board, BigInt &result) {
    std::vector<int> s;
    ordered_set t;

    _flatten(board, s);

    result.clear();
    // Converts s (base factorial) to base 2^32 and stores the result in result
    for (int i = 0; i < N*N; i++) {
        BigInt b(factorial(N*N-i-1));
        int order = (int)t.order_of_key(s[i]);
        BigInt v = { s[i] - order - 1 };
        t.insert(s[i]);

        BigInt product;
        mul(b, v, product);

        BigInt temp(result);
        add(temp, product, result);
    }
}

// This is currently the main function, this will soon be moved to main.cpp when I get around to it
int main() {
    printf("Doing hashing test\n");
    Board<5> board;
    BigInt h;
    board_hash<5>(board, h);
    disp(h);
    printf("Doing hashing test with slightly different board\n");
    board.tiles[0][0] = 5; // Digits 90-94 of PI (after decimal place)
    board.tiles[0][1] = 3;
    board.tiles[0][2] = 4;
    board.tiles[0][3] = 2;
    board.tiles[0][4] = 1;
    board_hash<5>(board, h);
    disp(h);
}
