#include "game_00.h"

MATCH void func_801BFAC4(void) {
    u8* work;
    s32 i;

    i = 0;
    while (i < (s32)g_PartySize) {
        work        = (u8*)g_BattlePartyBattlers + i * BATTLE_PARTY_STRIDE;
        g_GameState = (GameState*)work;
        g_SpadWork  = (Actor*)work;
        func_8014D978();
        i++;
    }
}
