#ifndef COMMON_COPY_H
#define COMMON_COPY_H

#include "types.h"

/* Copy units: records that exist only so a struct assignment gives the
 * retail block move. GCC 2.7.2 copies a word-aligned struct with lw/sw
 * pairs, unrolled into a 16-byte loop past 16 bytes, and a byte-aligned one
 * with lwl/lwr and swl/swr; a plain array or memcpy gives neither. The size
 * and alignment are the whole contract, so the members carry no meaning. */

/* Four aligned words: the 16-byte step of the block-move loop. */
typedef struct CopyWords16 {
    u32 w[4];
} CopyWords16;

/* 8, 16 and 32 bytes at byte alignment: copied with unaligned word pairs. */
typedef struct CopyBytes8 {
    u8 b[8];
} CopyBytes8;

typedef struct CopyBytes16 {
    u8 b[16];
} CopyBytes16;

typedef struct CopyBytes32 {
    u8 b[32];
} CopyBytes32;

ASSERT_SIZE(CopyWords16, 0x10);
ASSERT_SIZE(CopyBytes8, 0x8);
ASSERT_SIZE(CopyBytes16, 0x10);
ASSERT_SIZE(CopyBytes32, 0x20);

#endif
