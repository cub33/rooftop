#include <iostream>
#include "libs/ecclib/hamming64.h"
#include "libs/ecclib/secded.h"

__int128_t flipBit(__int128_t x, int pos) {
    return x ^ ((__int128_t)1 << pos);
}

int main() {
    uint64_t x = 123456789;

    std::cout << "original: " << x << "\n";

    // ===== HAMMING =====
    auto enc = hammingEncode(x);
    auto corrupted = flipBit(enc, 7);

    auto dec = hammingDecode(corrupted);

    std::cout << "\n[HAMMING]\n";
    std::cout << "decoded (after error): " << dec << "\n";

    // ===== SECDED =====
    auto sec = secdedEncode(x);
    auto sec1BitError = flipBit(sec, 10);
    auto dec2 = secdedDecode(sec1BitError);

    std::cout << "\n[SECDED]\n";
    std::cout << "decoded (1-bit error): " << dec2 << "\n";
    auto sec2BitError = flipBit(flipBit(sec, 10), 6);
    auto dec3 = secdedDecode(sec2BitError);

    std::cout << "decoded (2-bit error): " << dec3 << " (should be -1)\n";

    return 0;
}