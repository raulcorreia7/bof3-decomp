#include "battle_15.h"

MATCH void func_800A82F8(void) {
    s32 index;

    index         = 0;
    D_801463B8[0] = 0;
    if (g_BattleGeneCount[0] != 0) {
        do {
            D_801463B8[0] = (D_801463B8[0] + D_800B4C7C[g_BattleGenes[index & BYTE_MASK]]);
            index++;
        } while ((u32)(index & BYTE_MASK) < g_BattleGeneCount[0]);
    }
}
