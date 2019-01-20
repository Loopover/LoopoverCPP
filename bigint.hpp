#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>

#define BIGINT_RADIX 4294967296LL

typedef std::vector<unsigned int> BigInt;
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

// Division by zero
class DivisionByZero {};

// Mem optimisations
void trim(BigInt &x);

// Greater than or equals operator
bool gte(const BigInt &first, const BigInt &second);

// Addition
void add(const BigInt &first, const BigInt &second, BigInt &result);

// Subtraction
// WARNING: Assumes first > second, anything else is undefined behaviour
void sub(const BigInt &first, const BigInt &second, BigInt &result);

// Multiplication
void mul(const BigInt &first, const BigInt &second, BigInt &result);

// Division
void div(const BigInt &dividend, const BigInt &divisor, BigInt &result);

// Display big integers to standard output
void disp(const BigInt &x);
