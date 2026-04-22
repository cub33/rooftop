#ifndef HAMMING_HPP
#define HAMMING_HPP
#include <cstdint>
bool pof2(int i);
int calcn(int m);
__int128_t hammingEncode(uint64_t x);
int64_t hammingDecode(__int128_t x);
#endif