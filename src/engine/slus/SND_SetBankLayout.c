#include "engine/slus/slus.h"

/* builds the window layout table for one bank: it reads a six-entry
 * record at layout_bank * 0x1C, accumulates the running x and y extents, and
 * stores the six layout entries (each a base pointer, an index, and a
 * accumulated size) into the D_80148A1C..D_80148A4C globals, with the first
 * four bytes of each entry mirrored into D_8014677C..D_801467F8.
 */
MATCH void SND_SetBankLayout(u32 layout_bank) {
    s32 off;
    /* FAKE: pin keeps the accumulator in v1. */
    MATCH_FAKE_PIN(s32, v, "v1");
    /* FAKE: pin keeps the width in a0. */
    MATCH_FAKE_PIN(s32, w, "a0");
    u8* layer2;
    /* FAKE: pin keeps the stride in v0. */
    MATCH_FAKE_PIN(s32, size, "v0");
    /* FAKE: pin keeps the end offset in t0. */
    MATCH_FAKE_PIN(s32, end, "t0");
    /* FAKE: pin keeps the next index in a2. */
    MATCH_FAKE_PIN(s32, next, "a2");
    /* FAKE: pin keeps the last index in a3. */
    MATCH_FAKE_PIN(s32, last, "a3");

    s32 fixed             = 0x8011A000;
    off                   = (layout_bank & BYTE_MASK) * 0x1C;
    D_8014678C            = 0;
    v                     = FIELD(s32, D_8018239C, off);
    layer2                = D_8014871C;
    D_80148A18            = fixed;
    ((u32*)D_80146780)[0] = fixed;
    v += fixed;
    D_80146788[0]             = v;
    w                         = FIELD(s32, D_80182348, off);
    D_80146784                = (s32)D_801486A0;
    D_80148A34                = v;
    D_801467A0                = 1;
    D_8014677C[0].spu_address = w;
    size                      = FIELD(s32, D_801823F0, off);
    w                         = FIELD(s32, D_8018239C, off + 4);
    v += size;
    w          = v + w;
    D_80148A1C = v;
    D_8014679C = w;
    D_80146794 = v;
    v          = FIELD(s32, D_80182348, off + 4);
    D_80146798 = (s32)layer2;
    D_80148A38 = w;
    D_801467B4 = 2;
    D_80146790 = v;
    size       = FIELD(s32, D_801823F0, off + 4);
    v          = FIELD(s32, D_8018239C, off + 8);
    w += size;
    v          = w + v;
    D_80148A20 = w;
    D_801467B0 = v;
    D_801467A8 = w;
    w          = FIELD(s32, D_80182348, off + 8);
    D_801467AC = (s32)D_80148798;
    D_80148A3C = v;
    D_801467C8 = 3;
    D_801467A4 = w;
    size       = FIELD(s32, D_801823F0, off + 8);
    w          = FIELD(s32, D_8018239C, off + 12);
    v += size;
    w = v + w;
    /* FAKE: do-while(0) scope steers regalloc. */
    do {
        D_80148A24 = v;
        D_80148A40 = w;
        D_801467C4 = w;
        D_801467BC = v;
        v          = FIELD(s32, D_80182348, off + 12);
        D_801467C0 = (s32)D_80148814;
        D_801467DC = 4;
        D_801467B8 = v;
        size       = FIELD(s32, D_801823F0, off + 12);
        end        = FIELD(s32, D_8018239C, off + 16);
        w += size;
        end        = w + end;
        D_801467D8 = end;
        D_801467D0 = w;
        v          = FIELD(s32, D_80182348, off + 16);
        D_801467D4 = (s32)D_80148890;
        D_801467F0 = 5;
        D_801467CC = v;
        next       = FIELD(s32, D_801823F0, off + 16);
        last       = FIELD(s32, D_8018239C, off + 20);
        next       = end + next;
        last       = next + last;
        D_801467EC = last;
        D_801467E4 = next;
        v          = FIELD(s32, D_80182348, off + 20);
        D_801467E8 = (s32)D_8014890C;
        D_80146804 = 6;
        D_801467E0 = v;
        size       = FIELD(s32, D_801823F0, off + 20);
        v          = FIELD(s32, D_8018239C, off + 24);
        size       = last + size;
        v          = size + v;
        D_80146800 = v;
        D_801467F8 = size;
        off        = FIELD(s32, D_80182348, off + 24);
        D_80148A28 = w;
        D_80148A44 = end;
        D_80148A2C = next;
        D_80148A48 = last;
    } while (0);
    D_80148A30 = size;
    D_80148A4C = v;
    D_801467F4 = off;
    D_801467FC = (s32)D_80148988;
}
