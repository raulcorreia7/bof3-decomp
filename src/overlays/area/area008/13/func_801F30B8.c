#include "area008_13.h"

MATCH void func_801F30B8(void) {
    volatile Actor* previous;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        SELF(Actor)->header.mode = 9;
        return;
    }
    previous                  = SELF(Actor);
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    SELF_SET(&g_BattlePartyBattlers[1]);
    if (g_Game.members[1].unk_58 == 8 && g_Game.members[1].unk_4A == 1) {
        Script_Select(1);
        D_801F53F4            = D_801F4680[RANDOM_MASK(3)];
        g_Self                = previous;
        previous->header.mode = 8;
    }
}
