#include "battle_03.h"

MATCH void func_801DF768(void) {
    if ((g_BattleSelectionLatch != 0u) && ((g_BattleMessageTurn->command.target == g_Task->slot) ||
                                           ((g_BattleMessageTurn->command.target & 0x80u) != 0u))) {
        g_Task->unk_07      = GFX_AllocPaletteFade((u8*)g_Task, 0, 0, 0, 0);
        g_Task->header.step = 1u;
    }
}
