#include "battle_15.h"

MATCH void func_80098B44(void) {
    u32 flags;

    flags = Item_GetFlags(g_MenuPanelTasks[16].unk_0A,
                          D_801C893C[g_MenuPanelTasks[16].unk_0A][g_MenuPanelTasks[16].unk_0C]);
    if ((flags & 0x20u) != 0u) {
        g_BattleActorTurn->command.target = Battle_TargetNext(3);
        g_Battle.ui_state                 = 1u;
    } else if (func_8009AF7C() != 0u) {
        g_BattleActorTurn->command.target = 0u;
        g_Battle.ui_state                 = 2u;
    } else {
        g_BattleActorTurn->command.target = Battle_TargetNext(0);
        g_Battle.ui_state                 = 2u;
    }
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1u;
}
