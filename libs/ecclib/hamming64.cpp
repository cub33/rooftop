#include <iostream>
#include <cmath>
using namespace std;

bool pof2 (int i) {
    return (i & (i - 1)) == 0;
}

int calcn (int m) { // calcn(64) = 71 btw
    int r = 0;
    while ((1 << r) < (m + r + 1)) {
        r++;
    }
    return m + r;
}

__int128_t hammingEncode(u_int64_t x) {
    int m = 64;
    int n = calcn(m);
    bool* data = new bool[n]();
    u_int64_t cx = x;
    for (int i = 1; i <= n; i++) {
        if (!pof2(i)) {
            data[i - 1] = cx & 1;
            cx >>= 1;
        }
    }

    for (int p = 1; p <= n; p <<= 1) {
        bool odd = false;
        for (int i = 1; i <= n; i++) {
            if (i & p) {
                odd ^= data[i - 1];
            }
        }
        data[p - 1] = odd;
    }

    __int128_t r = 0;
    for (int i = 0; i < n; i++) {
        r <<= 1;
        r ^= data[i];
    }
    delete[] data;
    return r;
}
__int64_t hammingDecode (__int128_t x) {
    int m = 64;
    int n = calcn(m);
    bool* data = new bool[n]();

    __int128_t cx = x;
    for (int i = n; i >= 1; i--) {
        data[i - 1] = cx & 1;
        cx >>= 1;
    }
    int syndrome = 0;
    for (int i = 1; i <= n; i <<= 1) {
        bool odd = false;
        for (int j = 1; j <= n; j++) {
            if (j & i) odd ^= data[j - 1];
        }
        if (odd) syndrome += i;
    }
    if (syndrome > 0 && syndrome <= n) data[syndrome - 1] ^= 1;

    u_int64_t r = 0;
    int bitpos = 0;
    for (int i = 1; i <= n; i++) {
        if (!pof2(i)) {
            r |= ((u_int64_t)data[i - 1] << bitpos);
            bitpos++;
        }
    }
    delete[] data;
    return r;
}