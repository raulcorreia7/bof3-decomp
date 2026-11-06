#include "game_00.h"

MATCH s8 func_801A7AD8(u8* entry, u8 count, u8 x, u8 y) {
    s32 i;
    s32 j;
    s32 kind;
    u16 key;

    for (i = 0; i < count; i++, entry += 5) {
        key = LOHU(g_GameAreaId);
        for (j = entry[4] - 1; j >= 0; j--) {
            if (entry[0] != key) {
                break;
            }
            if (entry[3] & 0x80) {
                if (x != entry[1]) {
                    continue;
                }
                if (y == entry[2] + j) {
                    /* Own branch to the kind test: jump2 would merge a continue. */
                    goto found;
                }
                continue;
            }
            if (x != entry[1] + j || y != entry[2]) {
                continue;
            }
        found:
            kind = entry[3] & 0xF;
            /* The literal address reloads the work-row byte on every test;
             * the g_BattlePartyBattlers[0].facing symbol is hoisted out of the loops by loop.c. */
            if (kind == 8 || kind == MEM(u8, 0x80145E98u)) {
                return i;
            }
            break;
        }
    }
    return -1;
}
