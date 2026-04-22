#ifndef HAMMING_HPP
#define HAMMING_HPP
#include <cstdint>
struct hpacket {
    __int128_t data;
    int m;
};
bool pof2(int i);
int calcn(int m);
hpacket hammingEncode(uint64_t x);
int64_t hammingDecode(hpacket in);
#endif