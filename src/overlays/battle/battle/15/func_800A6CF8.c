#include "battle_15.h"

MATCH s32 func_800A6CF8(u8 selection_id, u8 column_index) {
    u8 value;
    u8 count;
    u8 index;

    value = D_800B4D58[selection_id][column_index];
    if (value == GAME_NONE) {
        return 1;
    }
    count = g_BattleGeneCount[0];
    index = 0;
    if (count != 0) {
        do {
            if (g_BattleGenes[index] == value) {
                return 1;
            }
            index++;
        } while (index < count);
    }
    return 0;
}
