#include "battle_15.h"

MATCH void func_800A58F4(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(27);
        g_GfxPalettePending                             = 1;
        g_Battle.selection_latch                        = 0;
        g_BattleActorTurn->command.type                 = BATTLE_COMMAND_ABILITY;
        g_BattleMessageSlot[1]                          = 2;
        g_Battle.command_count                          = g_Battle.command_count + 1;
        ((u8*)D_801EB5B1)[((D_801EC328 - 1) & 0xF) * 8] = 1;
        g_Battle.phase.step                             = 1;
        g_Battle.phase.sub_step                         = 0;
        g_Battle.ui_step                                = 0;
        g_Battle.ui_state                               = 0;
    }
}
