#include "battle_15.h"

MATCH void func_800A58F4(void) {
    if (EMI_IsReady() != 0) {
        GFX_CopyPalette(27);
        g_GfxPalettePending                                    = 1;
        g_Battle.selection_latch                               = 0;
        g_BattleActorTurn->command.type                        = BATTLE_COMMAND_ABILITY;
        g_BattleMessageSlot[1]                                 = 2;
        g_Battle.command_count                                 = g_Battle.command_count + 1;
        g_BattleMessages[((D_801EC328 - 1) & 0xF)].record_type = 1;
        g_Battle.phase.step                                    = 1;
        g_Battle.phase.sub_step                                = 0;
        g_Battle.ui_step                                       = 0;
        g_Battle.ui_mode                                       = 0;
    }
}
