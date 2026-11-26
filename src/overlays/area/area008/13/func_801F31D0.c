#include "area008_13.h"

MATCH void func_801F31D0(void) {
    volatile Actor* previous;
    u8*             table;

    previous                  = SELF(Actor);
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    SELF_SET(&g_BattlePartyBattlers[1]);
    Script_Select(1);
    table        = (u8*)g_GameState;
    table[0x118] = (table[0x118] & 0xBF);
    g_Self       = previous;
    Actor_Clear();
}
