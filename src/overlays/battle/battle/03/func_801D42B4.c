#include "battle_03.h"

MATCH void func_801D42B4(void) {
    u8 i;

    if (D_801EC2E4 == 0) {
        if (D_801EB5A8 != 0) {
            for (i = 0; i < 32; i++) {
                g_TextVariables[0][i] = 0;
            }
            for (i = 0; i < 8; i++) {
                g_TextVariables[0][i] = g_BattleEnemyBattlers[D_801ED9B0[D_801EB5A8 - 1].owner_index].name[i];
            }
            BattleStageSelectionRingRecord(1, 0, Resource_GetText(D_801ED9B0[D_801EB5A8 - 1].panel_id));
            D_801EB5A8 -= 1;
        } else {
            g_BattleStep    = 4;
            g_BattleSubStep = 0;
        }
    }
}
