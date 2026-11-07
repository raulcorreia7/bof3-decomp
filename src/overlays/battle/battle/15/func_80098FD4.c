#include "battle_15.h"

MATCH void func_80098FD4(void) {
    u8* cursor;
    u8* group;

    SND_PlayCue(EMI_CUE_ID(1, 4));
    cursor                          = &g_MenuPanelTasks[16].unk_0C;
    group                           = cursor - 2;
    g_BattleSelectionLatch          = 0u;
    g_BattleActorTurn->command.type = BATTLE_COMMAND_ITEM;
    g_BattleMessageSlot[1]          = 2u;

    g_BattleCommandCount += 1u;
    D_801EB5B1[((D_801EC328 - 1) & 0xF) * 8] = 1u;
    g_BattleActorTurn->choice                = *cursor;
    if (D_801C8950[*group][*cursor] >= 2u) {
        D_801C8950[*group][*cursor] -= 1u;
    } else {
        /* FAKE: block boundary keeps the group read base-relative off the cursor la. */
        ORDER_FENCE();
        D_801C893C[*group][*cursor] = 0;
        D_801C8950[*group][*cursor] = 0;
    }
    func_8009B20C();
    g_BattleStep    = 1u;
    g_BattleSubStep = 0u;
    g_BattleUIStep  = 0u;
    g_BattleUIState = 0u;
}
