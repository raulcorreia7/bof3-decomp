#include "battle_15.h"

MATCH void func_800A82F8(void) {
    s32 idx;

    idx           = 0;
    D_801463B8[0] = 0;
    if (g_BattleGeneCount[0] != 0) {
        do {
            D_801463B8[0] = (u8)(D_801463B8[0] + D_800B4C7C[g_BattleGenes[idx & BYTE_MASK]]);
            idx++;
        } while ((u32)(idx & BYTE_MASK) < g_BattleGeneCount[0]);
    }
}
