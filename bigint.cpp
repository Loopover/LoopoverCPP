#include "bigint.hpp"

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
        BigInt intermediate;
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
    trim(result);
}

// Assumes first > second, anything else is undefined behaviour
void sub(const BigInt &first, const BigInt &second, BigInt &result) {
    result.clear();
    ll carry = 0;
    for (int i = 0; i < first.size(); i++) {
        ll s = second[i] + carry;
        if (s > first[i]) {
            carry = 1;
            result.push_back((int)(first[i] - s + BIGINT_RADIX));
        } else {
            carry = 0;
            result.push_back((int)(first[i] - s));
        }
    }
    trim(result);
}

bool gte(const BigInt &first, const BigInt &second) {
    if (first.size() > second.size()) {
        return true;
    }
    if (second.size() > first.size()) {
        return false;
    }
    for (int i = (int)first.size() - 1; i >= 0; i--) {
        if (first[i] > second[i]) {
            return true;
        }
        if (second[i] > first[i]) {
            return false;
        }
    }
    return true;
}

// Short division
void div(const BigInt &dividend, const BigInt &divisor, BigInt &result) {
    if (divisor.empty()) {
        throw DivisionByZero();
    }
    result.clear();
    // Disassembled BigInt - back is most significant digit
    std::vector<bool> v;
    for (int i = 0; i < dividend.size(); i++) {
        for (int j = 0; j < 32; j++) {
            v.push_back((bool)((dividend[i] >> j) & 1));
        }
    }
    BigInt rem = { 0 };
    BigInt d = { 2 };
    BigInt o = { 1 };
    BigInt z = { 0 };
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        BigInt temp;
        BigInt temp2(result);

        mul(rem, d, temp);
        mul(temp2, d, result);

        if (v[i]) {
            add(temp, o, rem);
        } else {
            add(temp, z, rem);
        }

        if (gte(rem, divisor)) {
            BigInt temp3(result);
            BigInt temp4(rem);

            add(temp3, o, result);
            sub(temp4, divisor, rem);
        }
    }
    trim(result);
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
    for (int i = 0; i < 40; i++) {
        BigInt b(a);
        mul(b, exp, a);
        disp(a);
    }
    printf("Division test...\n");
    for (int i = 0; i < 40; i++) {
        BigInt b(a);
        div(b, exp, a);
        disp(a);
    }
    return 0;
}

int _fib_test() {
    BigInt a = { 0 };
    BigInt b = { 1 };
    BigInt c = { 1 };
    printf("Fibonacci sequence in base 16 test...\n");
    for (int i = 0; i < 20; i++) {
        add(a, b, c);
        disp(c);
        add(b, c, a);
        disp(a);
        add(c, a, b);
        disp(b);
    }
    printf("Reverse fibonacci sequence...\n");
    for (int i = 0; i < 20; i++) {
        sub(b, a, c);
        disp(c);
        sub(a, c, b);
        disp(b);
        sub(c, b, a);
        disp(a);
    }
    return 0;
}
