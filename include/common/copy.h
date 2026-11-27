#ifndef COMMON_COPY_H
#define COMMON_COPY_H

#include "types.h"

/* Copy units: records that exist only so a struct assignment gives the
 * retail block move. GCC 2.7.2 copies a word-aligned struct with lw/sw
 * pairs, unrolled into a 16-byte loop past 16 bytes, and a byte-aligned one
 * with lwl/lwr and swl/swr; a plain array or memcpy gives neither. The size
 * and alignment are the whole contract, so the members carry no meaning. */

/* Four aligned words: the 16-byte step of the block-move loop. */
typedef struct Cpy16 {
    u32 w[4];
} Cpy16;

/* 8, 16 and 32 bytes at byte alignment: copied with unaligned word pairs. */
typedef struct Cpy8u {
    u8 b[8];
} Cpy8u;

typedef struct Cpy16u {
    u8 b[16];
} Cpy16u;

typedef struct Cpy32u {
    u8 b[32];
} Cpy32u;

/* The word after a run of Cpy16 steps, stored as its own block. */
#define COPY_TAIL_WORD(dst, src) do { (dst)->w[0] = (src)->w[0]; } while (0)

ASSERT_SIZE(Cpy16, 0x10);
ASSERT_SIZE(Cpy8u, 0x8);
ASSERT_SIZE(Cpy16u, 0x10);
ASSERT_SIZE(Cpy32u, 0x20);

#endif
