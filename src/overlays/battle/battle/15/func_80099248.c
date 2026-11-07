#include "battle_15.h"

MATCH void func_80099248(void) {
    u16 held;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_BattleUIState = 3u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_BattleUIState = 2u;
        return;
    }
    if ((INPUT_REPEATED(held, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) == 0) {
        return;
    }
    if ((Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]) & 0x80u) != 0u) {
        g_BattleMessageTurn->command.target ^= 0xC0u;
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
