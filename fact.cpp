#include "fact.h"

std::vector<BigInt> cache;

BigInt factorial(int x) {
    if (cache.empty()) {
        cache.push_back({ 1 });
    }
    while (x >= cache.size()) {
        BigInt f = { (int)cache.size() };
        BigInt r;
        mul(cache.back(), f, r);
        cache.emplace_back(r);
    }
    return cache[x];
}
