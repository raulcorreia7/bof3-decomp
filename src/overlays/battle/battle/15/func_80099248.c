#include "battle_15.h"

MATCH void func_80099248(void) {
    u16 held;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_state = 3u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_state = 2u;
        return;
    }
    if ((INPUT_REPEATED(held, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) == 0) {
        return;
    }
    if ((Item_GetFlags(g_MenuPanelTasks[16].unk_0A, D_801C893C[g_MenuPanelTasks[16].unk_0A][g_MenuPanelTasks[16].unk_0C]) & 0x80u) != 0u) {
        g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
