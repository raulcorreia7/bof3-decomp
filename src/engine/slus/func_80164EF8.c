#include "engine/slus/slus.h"

typedef struct {
    s32 w[4];
} Quad;

/* copies one record, patches 6 bytes, recalculates it, then flags 4
 * field comparisons.
 */
MATCH void func_80164EF8(s32 index, u8* patch, u8* flags, u16* values) {
    Character copy;
    u16*      org[4];
    u16*      loc[4];
    s32*      src;
    /* FAKE: retail computes the record base in v0. */
    MATCH_REG(s32*, record, "v0");
    s32* dst;
    s32* end;
    u8   i;

    dst    = (s32*)&copy;
    record = (s32*)(&g_Characters[index & BYTE_MASK]);
    src    = record;
    end    = record + 0x28;
    org[0] = &((Character*)src)->power;
    org[1] = &((Character*)src)->defense;
    org[2] = &((Character*)src)->intellect;
    org[3] = &((Character*)src)->agility;
    loc[0] = &copy.power;
    loc[1] = &copy.defense;
    loc[2] = &copy.intellect;
    loc[3] = &copy.agility;
    do {
        *(Quad*)dst = *(Quad*)src;
        src += 4;
        dst += 4;
    } while (src != end);
    *dst                = *src;
    copy.weapon         = patch[0];
    copy.shield         = patch[1];
    copy.helmet         = patch[2];
    copy.armor          = patch[3];
    copy.accessories[0] = patch[4];
    copy.accessories[1] = patch[5];
    Char_RebuildStats(&copy);
    for (i = 0; i < 4; i++) {
        flags[i]  = 0;
        values[i] = *loc[i];
        if (*org[i] < *loc[i]) {
            flags[i] = 3;
        }
        if (*org[i] > *loc[i]) {
            flags[i] = 2;
        }
    }
}
