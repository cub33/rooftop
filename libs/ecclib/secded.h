#ifndef SECDED_HPP
#define SECDED_HPP
#include <cstdint>
__int128_t secdedEncode(uint64_t x);
int64_t secdedDecode(__int128_t x);
#endif