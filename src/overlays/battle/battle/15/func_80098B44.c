#include "battle_15.h"

MATCH void func_80098B44(void) {
    u32 flags;

    flags = Item_GetFlags(g_MenuPanelTasks[16].unk_0A,
                          D_801C893C[g_MenuPanelTasks[16].unk_0A][g_MenuPanelTasks[16].unk_0C]);
    if ((flags & 0x20u) != 0u) {
        g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(3);
        g_BattleUIState                   = 1u;
    } else if (func_8009AF7C() != 0u) {
        g_BattleActorTurn->command.target = 0u;
        g_BattleUIState                   = 2u;
    } else {
        g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(0);
        g_BattleUIState                   = 2u;
    }
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1u;
}
