#include <iostream>
#include <cmath>
using namespace std;

#include "hamming64.h"
__int128_t secdedEncode(uint64_t x) {
    __int128_t h = hammingEncode(x);
    __int128_t hx = h;
    bool odd = false;
    while (hx) {
        odd ^= (hx & 1);
        hx >>= 1;
    }
    return (h << 1) | odd;
}

__int64_t secdedDecode(__int128_t x) {
    bool parity_bit = (x & 1);
    __int128_t h = (x >> 1);

    __int128_t hx = h;
    bool odd = false;
    while (hx) {
        odd ^= (hx & 1);
        hx >>= 1;
    }

    int m = 64;
    int n = calcn(m);
    bool* data = new bool[n]();
    __int128_t cx = h;
    for (int i = n; i >= 1; i--) {
        data[i - 1] = (cx & 1);
        cx >>= 1;
    }

    int syndrome = 0;
    for (int i = 1; i <= n; i <<= 1) {
        bool bit = false;
        for (int j = 1; j <= n; j++) {
            if (j & i) bit ^= data[j - 1];
        }
        if (bit) syndrome += i;
    }

    if (odd == parity_bit) {
        if (syndrome == 0) {
            delete[] data;
            return hammingDecode(h);
        }
        delete[] data;
        return -1;
    }

    if (syndrome == 0) {
        delete[] data;
        return hammingDecode(h);
    }

    if (syndrome > 0 && syndrome <= n) {
        data[syndrome - 1] ^= 1;
        __int128_t corrected = 0;
        for (int i = 0; i < n; i++) {
            corrected = (corrected << 1) | data[i];
        }
        delete[] data;
        return hammingDecode(corrected);
    }

    delete[] data;
    return -1;
};