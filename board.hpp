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
        int total_moves;
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
        void do_move(Move op, int ind) {
            int temp[N];
            switch (op) {
                case Up:
                    // Index is the column
                    for (int i = 0; i < N; i++) {
                        temp[i] = this->tiles[i][ind];
                    }
                    for (int i = 0; i < N; i++) {
                        this->tiles[i][ind] = temp[(i+1)%N];
                    }
                    break;
                case Right:
                    for (int i = 0; i < N; i++) {
                        temp[i] = this->tiles[ind][i];
                    }
                    for (int i = 0; i < N; i++) {
                        this->tiles[ind][(i+1)%N] = temp[i];
                    }
                    break;
                case Down:
                    // Index is the column
                    for (int i = 0; i < N; i++) {
                        temp[i] = this->tiles[i][ind];
                    }
                    for (int i = 0; i < N; i++) {
                        this->tiles[i][ind] = temp[(i+1)%N];
                    }
                    break;
                case Left:
                    for (int i = 0; i < N; i++) {
                        temp[i] = this->tiles[ind][i];
                    }
                    for (int i = 0; i < N; i++) {
                        this->tiles[ind][(i+1)%N] = temp[i];
                    }
                    break;
            }
            this->total_moves++;
        }
        int get_total_moves() {
            return this->total_moves;
        }
        void disp() {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (j != N-1) {
                        printf("%4d ", this->tiles[i][j]);
                    } else {
                        printf("%4d\n", this->tiles[i][j]);
                    }
                }
            }
        }
};
