#include "game_00.h"

/* Standalone TU: game_00.h still declares this function as void(s16, s16),
 * which contradicts the observed s32 0/1 return, so shared decls stay local
 * until the header is corrected by its owner. */

#ifdef NON_MATCHING
NON_MATCHING bool func_801A0048(s32 cell_x, s32 cell_y) {
    GameLocaleBank** banks;
    GameLocaleBank*  bank;
    GameLocale*      entry;
    u32*             keys;
    u8*              counts;
    u8*              base;
    u8*              aux;
    u8*              tab;
    u16              seed;
    u32              hi;
    u32              mid;
    u32              mask;
    s32              left;
    s32              span;
    s32              x;
    s32              y;
    u16              index;
    u8               n;
    u8               kind;
    u8               reread;

    banks = g_AreaLoads;
    left  = banks[g_GameAreaId]->outer;
    if (left < 0)
        return true;
    x    = cell_x & BYTE_MASK;
    y    = cell_y & BYTE_MASK;
    tab  = g_SaveData.scene_flag_words;
    mask = 0xFF8000;
    do {
        entry = &banks[g_GameAreaId]->entries[left];
        span  = (s32)entry->span - 1;
        if (span >= 0) {
            do {
                if (entry->mode != 0) {
                    if (x == entry->cx) {
                        span -= 1;
                        if (y == (s32)entry->cy + span)
                            goto found;
                    } else {
                        span -= 1;
                    }
                } else if (x == (s32)entry->cx + span) {
                    span -= 1;
                    if (y == entry->cy)
                        goto found;
                } else {
                    span -= 1;
                }
            } while (span >= 0);
        }
        left -= 1;
    } while (left >= 0);
    return true;

found:
    if (entry->key == 0xFFFF) {
        index  = entry->index;
        bank   = banks[g_GameAreaId];
        keys   = bank->keys;
        counts = bank->counts;
        n      = counts[index];
        base   = (u8*)keys[index];
        left   = 0;
        if (n != 0) {
            aux = base + 7;
            do {
                left += 1;
                if (SYS_TestFlag(tab + ((u32)aux[-1] << 3), aux[0]) != 0) {
                    base += 0x0A;
                    break;
                }
                aux += 0x0A;
                base += 0x0A;
            } while (left < (s32)n);
        }
        hi   = *(u16*)(base + 2);
        seed = *(u16*)base;
        hi <<= 8;
        g_GameContextSeed = seed;
        mid               = *(u16*)(base + 4);
        g_GameEntryPosX   = hi & mask;
        mid <<= 8;
        g_GameEntryPosY = mid & mask;
        kind            = base[8];
    } else {
        g_GameContextSeed = entry->key;
        g_GameEntryPosX   = ((u32)entry->index << 8) & mask;
        g_GameEntryPosY   = ((u32)entry->alt << 8) & mask;
        kind              = entry->kind;
    }
    g_GameContextKind = kind;
    reread            = g_GameContextKind;
    SP_REF(s8, 0x01u) = (s8)((reread >> 4) & 7);
    g_GameContextKind = reread & 0x8F;
    func_801A02E8();
    func_801A0380((u32)D_80143F16, (u32)D_80143F1A, g_GameContextSeed);
    return false;
}
#else
INCLUDE_ASM(func_801A0048);
#endif
