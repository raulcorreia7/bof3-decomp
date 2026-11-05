#include "battle_03.h"

MATCH void func_801D3050(void) {
    volatile u8* battler;
    u8           i;

    func_801D4850();
    if (g_BattleSubStep == 2 && !BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        for (i = 0; i < 32; i++) {
            g_TextVariables[0][i] = 0;
        }
        i       = 0;
        battler = &g_BattleActiveBattler;
        do {
            s32 row;

            row                   = *battler - 3;
            g_TextVariables[0][i] = D_801EB6A4[row][i];
            i++;
        } while (i < 8);
        func_801D9484();
        func_801DE560(2, 0, 0, 0x2D, Resource_GetText(CALLBACK_SLOT_IDLE));
    }
    g_BattleMode    = 3;
    g_BattleStep    = 0;
    g_BattleSubStep = 0;
}
