#include "battle_15.h"

MATCH void func_800A58F4(void) {
    if (EMI_LoaderIsReady() != 0) {
        GFX_CopyPalette(0x1B);
        g_GfxPalettePending                             = 1;
        g_BattleSelectionLatch                          = 0;
        g_BattleMessageTurn->command.type               = BATTLE_COMMAND_ABILITY;
        g_BattleMessageSlot[1]                          = 2;
        g_BattleCommandCount                            = g_BattleCommandCount + 1;
        ((u8*)D_801EB5B1)[((D_801EC328 - 1) & 0xF) * 8] = 1;
        g_BattleStep                                    = 1;
        g_BattleSubStep                                 = 0;
        g_BattleUIStep                                  = 0;
        g_BattleUIState                                 = 0;
    }
}
