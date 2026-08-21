/************************************************************
 *  Author:         Nicholas Tibbetts
 *  Date:           08/21/2026 T04:20:43
 *  License:        Copyright 2026 Nic Tibbetts
 *  Description:    Cursed Coding
 ***********************************************************/

#include <bits/stdc++.h>
using namespace std;

int main()
{ unsigned long long __[] = {
        ((0xACULL << 56) | (0xBEULL << 48) | (0x1AULL << 40) | (0xEBULL << 32) |
         (0x3AULL << 24) | (0xF9ULL << 16) | (0x91ULL << 8) | 0xEEULL),
        ((0x4EULL << 56) | (0x69ULL << 48) | (0x63ULL << 40) | (0x60ULL << 32) |
         (0x81ULL << 24) | (0x85ULL << 16) | (0x8FULL << 8) | 0x91ULL),
        ((0x4EULL << 56) | (0x69ULL << 48) | (0x63ULL << 40) | (0x54ULL << 32) |
         (0x69ULL << 24) | (0x62ULL << 16) | (0x62ULL << 8) | 0x73ULL) // ~:)
    }, ___ = (2[__] ^ (2[__] >> 11)) *
             ((2[__] ^ (2[__] >> 23) ^ (2[__] << 17)) | -~0ULL);
    for (auto _ = ~+~0; _ < static_cast<int>(((2[__] & 0xFULL) << 2) | !0); ++_)
    { //!
        auto ____ = [&__, &___](auto _, auto $)
        { auto _____ = static_cast<unsigned char>(
                (((($ >> 3)[__] ^ 2[__]) >> (($ & 7) << 3)) & ((1ULL << 8) + ~0ULL)) ^
                (((___ ^ ((2[__] >> ((_ & 7) << 3)) & ((1ULL << 8) + ~0ULL)) ^
                   (static_cast<unsigned long long>(_ + $) * 2[__])) *
                  ((2[__] ^ (2[__] >> 23) ^ (2[__] << 17)) |-~0ULL)) >> 56));
            auto $_ = (_____ + ((2[__] >> ((_ & 7) << 3)) & 0xFFULL) + $) & 63;
            return ___ ^= (static_cast<unsigned long long>(_____ + !0) *
                           ((2[__] ^ (2[__] >> 29) ^ (2[__] << 7)) |
                          -~0ULL)) ^ (static_cast<unsigned long long>(_) 
                          * 2[__]) ^ $, ___ = ((___ << $_) | (___ >> ((-$_) & 63))) 
                          ^ 2[__], _____; }; 
                         cout << ____(_, (_ * ((2[__] >> 36) & 0xFULL) +
                         ((___ >> 28) & 0x1FULL) * ((2[__] >> 24) & 0xFULL) +
                         (2[__] >> 8 & 0xFULL)) % (((2[__] & 0xFULL) << 2) | !0));
    } cout << (char)((___ >> 60)^((2[__] >> 36) & 0xFULL));
}
