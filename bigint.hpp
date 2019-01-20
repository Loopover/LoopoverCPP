#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>

#define BIGINT_RADIX 2147483648LL

typedef std::vector<int> BigInt;
typedef long long ll;

// Mem optimisations
void trim(BigInt &x);

// Addition
void add(const BigInt &first, const BigInt &second, BigInt &result);

// Multiplication
void mul(const BigInt &first, const BigInt &second, BigInt &result);

// Display big integers to standard output
void disp(const BigInt &x);
