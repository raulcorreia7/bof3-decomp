#include "battle_15.h"

/* func_800A82F8 */
MATCH void Battle_SetGeneCount(void) {
    s32 index;

    index         = 0;
    D_801463B8[0] = 0;
    if (g_Battle.gene_count != 0) {
        do {
            D_801463B8[0] = (D_801463B8[0] + D_800B4C7C[g_Battle.genes[index & BYTE_MASK]]);
            index++;
        } while ((u32)(index & BYTE_MASK) < g_Battle.gene_count);
    }
}
