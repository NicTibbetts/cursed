# Cursed coding

```text
Author:      Nicholas Tibbetts
Date:        03/11/2024
Language:    C++
Description: Cursed Coding
```

A small experiment in making `Hello, World!` substantially more difficult to arrive at than necessary.

The program is intentionally kept compact. Most of the work is done with integer arithmetic, bit manipulation, C++ expression semantics, and a small stateful decoder rather than by hiding the operation behind a large amount of supporting code.

```holyc
/************************************************************
 *  Author:         Nicholas Tibbetts
 *  Date:           03/11/2024 T12:55:02
 *  License:        Copyright 2024 Nic Tibbetts
 *  Description:    Cursed Coding
 ***********************************************************/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    unsigned long long __[] = {
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
        {
            auto _____ = static_cast<unsigned char>(
                (((($ >> 3)[__] ^ 2[__]) >> (($ & 7) << 3)) &
                  ((1ULL << 8) + ~0ULL)) ^
                (((___ ^ ((2[__] >> ((_ & 7) << 3)) &
                           ((1ULL << 8) + ~0ULL)) ^
                   (static_cast<unsigned long long>(_ + $) * 2[__])) *
                  ((2[__] ^ (2[__] >> 23) ^ (2[__] << 17)) |
                   -~0ULL)) >> 56));

            auto $_ = (_____ + ((2[__] >> ((_ & 7) << 3)) & 0xFFULL) + $) & 63;

            return ___ ^= (static_cast<unsigned long long>(_____ + !0) *
                           ((2[__] ^ (2[__] >> 29) ^ (2[__] << 7)) |
                            -~0ULL)) ^
                          (static_cast<unsigned long long>(_) * 2[__]) ^ $,
                   ___ = ((___ << $_) | (___ >> ((-$_) & 63))) ^ 2[__],
                   _____;
        };

        cout << ____(_, (_ * ((2[__] >> 36) & 0xFULL) +
                         ((___ >> 28) & 0x1FULL) *
                         ((2[__] >> 24) & 0xFULL) +
                         (2[__] >> 8 & 0xFULL)) %
                        (((2[__] & 0xFULL) << 2) | !0));
    }

    cout << (char)((___ >> 60) ^ ((2[__] >> 36) & 0xFULL));
}
```

## Background

The first version of this program was mostly an exercise in hostile notation: packed character data, shifts, complements, unary operators, and expressions that were intentionally unpleasant to simplify.

That worked visually, but some of the complexity disappeared too quickly once the expressions were reduced. In particular, an expression that ultimately contributes zero may look complicated, but once that fact is found there is nothing left to investigate.

The later version was built around a different rule:

> If an expression looks important, it should preferably be important.

The current program still uses deliberately awkward notation, but most of the major expressions participate directly in the decoding process.

## Data layout

The program begins with three 64 bit words.

Reduced to hexadecimal, they are:

```text
ACBE1AEB3AF991EE
4E69636081858F91
4E69635469626273
```

The last value can be read byte for byte as ASCII:

```text
4E 69 63 54 69 62 62 73
 N  i  c  T  i  b  b  s
```

So the third word contains `NicTibbs`.

It is also used throughout the decoder.

For the rest of this document it is easier to refer to that word as `K`.

```holyc
K = 0x4E69635469626273ULL;
```

`K` is used in the initial state, loop length, ciphertext reconstruction, byte addressing, mask generation, feedback, rotation, and final output.

## Reversed array subscripting

The source frequently uses expressions such as:

```holyc
2[__]
```

rather than:

```holyc
__[2]
```

Array subscripting in C and C++ is defined in terms of pointer addition:

```holyc
a[b]
```

is equivalent to:

```holyc
*(a + b)
```

which means:

```holyc
2[__]
```

becomes:

```holyc
*(2 + __)
```

and refers to the same object as:

```holyc
__[2]
```

The same property is used later in:

```holyc
($ >> 3)[__]
```

which corresponds to:

```holyc
__[$ >> 3]
```

Since `$` is always in the range `0..12`, this selects either `__[0]` or `__[1]`.

## Initial state

The initial state is constructed with:

```holyc
___ = (2[__] ^ (2[__] >> 11)) *
      ((2[__] ^ (2[__] >> 23) ^ (2[__] << 17)) | -~0ULL);
```

Replacing `2[__]` with `K` gives:

```holyc
state =
    (K ^ (K >> 11)) *
    ((K ^ (K >> 23) ^ (K << 17)) | 1ULL);
```

The expression:

```holyc
-~0ULL
```

evaluates to `1ULL`.

`~0ULL` produces the maximum value of an `unsigned long long`. Negating it wraps modulo `2^64`, producing one.

The OR therefore guarantees that the second factor is odd.

For this value of `K`, the initial state is:

```text
332D620CBA7BEB9F
```

## Loop initialization

The loop begins with:

```holyc
auto _ = ~+~0;
```

Evaluating the unary operators from right to left:

```text
~0      = -1
+(-1)   = -1
~(-1)   = 0
```

so the loop begins at zero.

The limit is:

```holyc
((2[__] & 0xFULL) << 2) | !0
```

The low nibble of `K` is `3`.

```text
3 << 2 = 12
!0     = 1
12 | 1 = 13
```

There are therefore thirteen decoding iterations.

No literal `13` is present in the loop.

## Ciphertext reconstruction

The first two array elements are not used directly as the ciphertext.

The decoder begins with:

```holyc
($ >> 3)[__] ^ 2[__]
```

or, written conventionally:

```holyc
__[$ >> 3] ^ __[2]
```

Since `__[2]` is `K`, the actual packed data is reconstructed as:

```text
__[0] ^ K = E2D779BF539BF39D
__[1] ^ K = 00000034E8E7EDE2
```

The relevant byte is then selected using:

```holyc
(($ & 7) << 3)
```

which is equivalent to multiplying the low three bits of the position by eight.

The resulting encoded byte table is:

```text
Index   Byte
-----   ----
0       9D
1       F3
2       9B
3       53
4       BF
5       79
6       D7
7       E2
8       E2
9       ED
10      E7
11      E8
12      34
```

These bytes are not consumed sequentially.

## Constructing the byte mask

The expression:

```holyc
((1ULL << 8) + ~0ULL)
```

produces `0xFF`.

`1ULL << 8` is `256`, while `~0ULL` is `2^64 - 1`.

Unsigned addition wraps modulo `2^64`:

```text
256 + (2^64 - 1) = 255 mod 2^64
```

so the result is:

```text
00000000000000FF
```

This is used as the extraction mask.

The implementation relies on defined unsigned modular arithmetic rather than signed overflow.

## Character mask

The selected ciphertext byte is XORed with the high byte of a mixed 64 bit value.

Ignoring the notation, the calculation is approximately:

```holyc
keyByte = (K >> ((i & 7) * 8)) & 0xFF;

mask =
    ((state ^
      keyByte ^
      ((uint64_t)(i + pos) * K))
     * multiplier) >> 56;

plain = encoded ^ mask;
```

The mask therefore depends on:

* the current decoder state,
* the current output position,
* the selected ciphertext position,
* and `K`.

The message is not encoded using a fixed XOR value.

## Feedback

Once a character has been recovered, it is immediately fed back into the decoder.

The next quantity is:

```holyc
auto $_ =
    (_____ +
     ((2[__] >> ((_ & 7) << 3)) & 0xFFULL) +
     $) & 63;
```

In conventional notation:

```holyc
rotation = (plain + keyByte + pos) & 63;
```

The decoded character therefore affects the rotation applied to the decoder state.

The state update itself is performed inside the return statement:

```holyc
return ___ ^= ...,
       ___ = ...,
       _____;
```

This uses the built in comma operator.

Its behavior is equivalent to:

```holyc
state ^= ...;
state = ...;
return plain;
```

The first state update includes the recovered plaintext:

```holyc
state ^=
    ((uint64_t)(plain + 1) * feedbackMultiplier) ^
    ((uint64_t)i * K) ^
    pos;
```

As a result the state required to decode character `n + 1` depends on the plaintext recovered for character `n`.

A damaged or incorrectly recovered character therefore changes the subsequent decoding state.

## State rotation

The second state update is:

```holyc
___ = ((___ << $_) | (___ >> ((-$_) & 63))) ^ 2[__];
```

The shift pair implements a 64 bit rotate left:

```holyc
state = rotl(state, rotation) ^ K;
```

The complementary shift distance is obtained using:

```holyc
(-rotation) & 63
```

rather than explicitly calculating `64 - rotation`.

The state is then mixed with `K` again.

## Ciphertext addressing

The byte passed to the decoder is selected with:

```holyc
(_ * ((2[__] >> 36) & 0xFULL) +
 ((___ >> 28) & 0x1FULL) *
 ((2[__] >> 24) & 0xFULL) +
 (2[__] >> 8 & 0xFULL)) %
(((2[__] & 0xFULL) << 2) | !0)
```

With the relevant fields of `K` evaluated, this becomes:

```holyc
pos =
    (5 * i +
     9 * ((state >> 28) & 31) +
     2)
    % 13;
```

The ciphertext position therefore depends on the current state.

Since the current state depends on previously recovered plaintext, the order in which ciphertext is consumed also depends on previously recovered plaintext.

During a successful execution the positions are:

```text
10, 3, 1, 11, 4, 2, 5, 8, 12, 9, 7, 0, 6
```

This order is not stored anywhere in the program.

It is produced by the state transitions.

## Execution trace

A complete successful pass looks like this:

```text
i    state-before       pos   encoded   mask   output
--   ----------------   ---   -------   ----   ------
0    332D620CBA7BEB9F    10     E7       AF      H
1    D1E8869A1B4B13F5     3     53       36      e
2    C90B1A3264BD6FC4     1     F3       9F      l
3    7FA554C15B4D6FB9    11     E8       84      l
4    F050E4C2B3B6A04D     4     BF       D0      o
5    D8D03FB238BF18C8     2     9B       B7      ,
6    1CF1297B76F3F3F8     5     79       59      [space]
7    6DA723731CEDE5AD     8     E2       B5      W
8    2A826D2C1CD887D2    12     34       5B      o
9    8FA4DA90324B0126     9     ED       9F      r
10   E5D2075C854C3875     7     E2       8E      l
11   6C215A5187551238     0     9D       F9      d
12   63CAF34BB4E5EAD7     6     D7       F6      !
```

The resulting text is:

```text
Hello, World!
```

## Final character

The program ends with:

```holyc
cout << (char)((___ >> 60) ^
               ((2[__] >> 36) & 0xFULL));
```

After all thirteen state transitions:

```text
state = F296E40946886CA8
```

The high nibble is `0xF`.

The selected nibble of `K` is `0x5`.

```text
0xF ^ 0x5 = 0xA
```

`0x0A` is the newline character.

The line break is therefore derived partly from the final decoder state rather than stored directly.

## Overall structure

Stripped of the notation, the program is approximately:

```text
K = packed "NicTibbs"

derive initial state from K

repeat 13 times:

    derive next ciphertext position
        from index, state, and K

    reconstruct selected ciphertext byte
        using K

    derive a per character mask
        from state, position, index, and K

    plaintext = ciphertext XOR mask

    derive a rotation
        from plaintext, position, and K

    feed plaintext back into state

    rotate and remix state

    output plaintext

derive newline from final state and K
```

The unusual part is not any one operation. It is that the same small set of values is reused throughout the program.

`K` is simultaneously data, key material, configuration, and part of the state transition.

The plaintext is simultaneously output and feedback.

The decoder state is simultaneously part of the decryption key and part of the addressing scheme.

As a result, the program cannot be reduced cleanly into thirteen independent character calculations.

## Notes on the design

Several rules for this type of obfuscation:

1. Keep the whole program small.
2. Avoid helper functions or supporting machinery unless necessary.
3. Prefer defined C++ behavior over accidental compiler behavior.
4. Reuse existing values rather than introduce dedicated constants.
5. Make recovered plaintext participate in future decoding.
6. Avoid storing traversal order explicitly.
7. Avoid storing the final output directly.
8. Do not make an expression complicated if the complication disappears without consequence.
 
