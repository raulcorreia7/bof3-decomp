#include "battle_15.h"

MATCH void func_8009A664(void) {
    u16 entry;

    entry = g_Game.members[g_BattleMessageSlot[5]].u.turn.command.id;
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        g_Battle.ui_mode = 3;
        return;
    }
    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        g_Battle.ui_mode = 2;
        return;
    }
    if ((INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) && (Item_GetFlags(entry >> 8, entry & BYTE_MASK) & ITEM_USABLE_MENU)) {
        g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
