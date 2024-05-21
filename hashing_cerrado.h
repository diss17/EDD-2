#include <iostream>
#include <cmath>

using namespace std;

class HashFunctions {
public:
    HashFunctions(int tableSize) : n(tableSize) {
        A = (sqrt(5) - 1) / 2;
    }

    int h1(unsigned long long k) const {
        return k % n;
    }

    int h2(int k) const {
        float a = static_cast<float>(k) * A;
        a -= static_cast<int>(a);
        return static_cast<int>(n * a);
    }

    int linear_probing(unsigned long long k, int i) const {
        return (h1(k) + i) % n;
    }

    int quadratic_probing(unsigned long long k, int i) const {
        return (h1(k) + i + 2 * i * i) % n;
    }

    int double_hashing(int k, int i) const {
        return (h1(k) + i * (h2(k) + 1)) % n;
    }

private:
    int n;
    float A;
};
