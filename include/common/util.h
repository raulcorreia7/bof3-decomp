#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#include "types.h"

/* ABS comes from PsyQ <abs.h>. Not abs(): ABS(a - b) recomputes the difference on the
 * negative path, abs() negates the computed value. */
#include <abs.h>

/* LO/HI read the little-endian halves of an object without copying. */

/* The byte value that means no slot, index or result in a byte field. It is
 * compared, never used as a mask. */
#define GAME_NONE                0xFF

/* The low byte and low halfword of a value: `x & BYTE_MASK`. A mask, never a sentinel (GAME_NONE). */
#define BYTE_MASK                0xFF
#define HALF_MASK                0xFFFF

/* The number of values a byte id can take. */
#define BYTE_VALUE_COUNT         256

/* Bit arrays of u32 words, one bit per id: bit `i` is bit `i % 32` of word `i / 32`. */
#define BIT_ARRAY_WORDS(bits)    ((bits) / 32)
#define BIT_ARRAY_TEST(words, i) ((words)[(i) >> 5] & BIT((i) & 0x1F))
#define BIT_ARRAY_SET(words, i)  ((words)[(i) >> 5] |= BIT((i) & 0x1F))

/* The element count of an array declared in scope. */
#define ARRAY_COUNT(a)           (sizeof(a) / sizeof((a)[0]))

/* Bits and arithmetic. BIT is a signed int like the open-coded `1 << n`. */
#define BIT(n)                   (1 << (n))
#define MIN(a, b)                (((a) < (b)) ? (a) : (b))
#define MAX(a, b)                (((a) > (b)) ? (a) : (b))

/* A random value below the next power of two: the mask must be 2^n - 1. */
#define RANDOM_MASK(mask)        (rand() & (mask))

/* A random value from 0 to count - 1; rand() % count, which compiles apart from a mask. */
#define RANDOM_MOD(count)        (rand() % (count))

/* A percentage roll from 0 to 99, tested against a chance in percent. */
#define RANDOM_PERCENT()         RANDOM_MOD(100)

/* LO/HI name the little-endian half or byte of the object: the expansion is
 * the same cast-and-dereference expression the retail code compiles. The
 * argument stays addressable, so these are lvalues. */
#define LOB(x)                   (*(s8*)&(x))
#define LOBU(x)                  (*(u8*)&(x))
#define LOH(x)                   (*(s16*)&(x))
#define LOHU(x)                  (*(u16*)&(x))
#define HIH(x)                   (((s16*)&(x))[1])
#define LOW(x)                   (*(s32*)&(x))
#define LOWU(x)                  (*(u32*)&(x))

#endif
