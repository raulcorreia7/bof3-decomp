#include "battle_15.h"

MATCH u8 func_800A6D84(void) {
    u8 index;

    for (index = 0; index < g_BattleGeneCount[0]; index++) {
        if ((g_BattleGenes[index] == 0x10) && (g_BattleLivingPartyCount == 3)) {
            return func_800A805C();
        }
    }
    return 0;
}
