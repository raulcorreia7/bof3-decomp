#include "battle_15.h"

MATCH void func_8009A664(void) {
    u16 entry;

    entry = g_BattlePartyBattlers[g_BattleMessageSlot[5]].turn.command.id;
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        g_BattleUIState = 3;
        return;
    }
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        g_BattleUIState = 2;
        return;
    }
    if ((INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) &&
        (Item_GetFlags(entry >> 8, entry & BYTE_MASK) & 0x80)) {
        g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
}
