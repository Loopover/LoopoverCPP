#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>

#define BIGINT_RADIX 2147483648LL

typedef std::vector<int> BigInt;
typedef long long ll;

namespace std {
    template <>
    class hash<BigInt> {
        public:
            size_t operator()(const BigInt &key) const {
                size_t result = 0;
                std::hash<int> h;
                for (int i = 0; i < key.size(); i++) {
                    result ^= h(key[i]);
                }
                return result;
            }
    };
}

// Mem optimisations
void trim(BigInt &x);

// Addition
void add(const BigInt &first, const BigInt &second, BigInt &result);

// Multiplication
void mul(const BigInt &first, const BigInt &second, BigInt &result);

// Display big integers to standard output
void disp(const BigInt &x);
