#include "battle_15.h"

MATCH void func_8009A664(void) {
    u16 entry;

    entry = g_Game.members[g_BattleMessageSlot[5]].u.turn.command.id;
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        g_Battle.ui_mode = 3;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        g_Battle.ui_mode = 2;
        return;
    }
    if ((INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL) & INPUT_DIRECTIONAL) && (Item_GetFlags(entry >> 8, entry & BYTE_MASK) & ITEM_USABLE_MENU)) {
        g_BattleActorTurn->command.target ^= BATTLE_TARGET_BOTH_SIDES;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
