#include "bigint.h"

// Mem optimisations
void trim(BigInt &x) {
    while (!x.empty() && x.back() == 0) {
        x.pop_back();
    }
    x.shrink_to_fit();
}

// Addition
void add(const BigInt &first, const BigInt &second, BigInt &result) {
    result.clear();
    ll carry = 0;
    for (size_t i = 0; i < std::max(first.size(), second.size()); i++) {
        ll sum = carry;
        if (i < first.size()) {
            sum += first[i];
        }
        if (i < second.size()) {
            sum += second[i];
        }
        carry = sum / BIGINT_RADIX;
        ll output = sum % BIGINT_RADIX;
        result.push_back((int)output);
    }
    if (carry > 0) {
        result.push_back((int)carry);
    }
    trim(result);
}

// Multiplication
void mul(const BigInt &first, const BigInt &second, BigInt &result) {
    result.clear();
    for (size_t i = 0; i < first.size(); i++) {
        BigInt intermediate = {};
        for (int j = 0; j < (int)i; j++) {
            intermediate.push_back(0);
        }
        ll carry = 0;
        for (size_t j = 0; j < second.size(); j++) {
            ll prod = first[i] * (ll)second[j] + carry;
            carry = prod / BIGINT_RADIX;
            ll output = prod % BIGINT_RADIX;
            intermediate.push_back((int)output);
        }
        if (carry > 0) {
            intermediate.push_back((int)carry);
        }
        BigInt temp2(result);
        add(temp2, intermediate, result);
    }
}

// Display big integers to standard output
void disp(const BigInt &x) {
    for (int i = (int)x.size() - 1; i >= 0; i--) {
        if (i > 0) {
            printf("%x ", x[i]);
        } else {
            printf("%x\n", x[i]);
        }
    }
}

// Testing functions for addition and multiplication.
int _exp_test() {
    BigInt a = { 1 };
    BigInt exp = { 17 };
    printf("Exponentiation test...\n");
    for (int i = 0; i < 20; i++) {
        BigInt b(a);
        mul(b, exp, a);
        disp(a);
    }
    return 0;
}

int _fib_test() {
    BigInt a = { 0 };
    BigInt b = { 1 };
    BigInt c = { 1 };
    printf("Fibonacci sequence in base 16 test...\n");
    for (int i = 0; i < 100; i++) {
        add(a, b, c);
        disp(c);
        add(b, c, a);
        disp(a);
        add(c, a, b);
        disp(b);
    }
    return 0;
}
