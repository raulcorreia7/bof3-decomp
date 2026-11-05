#include "game_00.h"

MATCH void func_801BDAB8(void) {
    s32 index;
    s32 off;

    for (index = g_PartySize - 1; index >= 0; index--) {
        off = index * BATTLE_PARTY_STRIDE;
        if ((((u8*)g_BattlePartyBattlers)[off] & 0x40) == 0) {
            g_Task = (Actor*)((u8*)g_BattlePartyBattlers + off);
            if (g_GameStateIndex == GAME_REQUEST_BATTLE) {
                Area_SetDrawMode();
            } else {
                func_8014D290();
            }
        }
    }
}
