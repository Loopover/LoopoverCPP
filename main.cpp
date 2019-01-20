#include <cstdio>
#include <cstdlib>
#include <unordered_set>
#include <vector>
#include <thread>
#include <mutex>

#include "boardhashing.hpp"
#include "bigint.hpp"
#include "board.hpp"

std::unordered_set<BigInt> seen;

std::vector<int> counts;
int total;

int main() {
    return board_test();
}
