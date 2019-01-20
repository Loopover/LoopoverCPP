#pragma once

#include <cstdio>
#include <cstdlib>

enum Move {
    Up,
    Right,
    Down,
    Left
};

template <int N>
class Board {
    public:
        int tiles[N][N];
        Board() {
            // Initialise board to default state
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    this->tiles[i][j] = N*i+j+1;
                }
            }
        }
        void do_move(Move op, int index) {
            
        }
};
