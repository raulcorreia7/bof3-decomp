#include "area008_13.h"

MATCH void func_801F2E1C(void) {
    volatile Actor* previous;
    u8              tmp;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        SELF(Actor)->header.mode = 9;
        return;
    }
    if (g_ScriptVars[1] == 1) {
        g_ScriptVars[2]          = 5;
        g_ScriptVars[1]          = 2;
        SELF(Actor)->header.mode = 6;
        return;
    }
    tmp        = (D_801F53F4 - 1);
    D_801F53F4 = tmp;
    if ((tmp & BYTE_MASK) < 2) {
        g_ScriptVars[2]           = 2;
        previous                  = SELF(Actor);
        WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
        SELF_SET(&g_BattlePartyBattlers[1]);
        Script_Select(1);
        D_801F53F4            = D_801F4680[RANDOM_MASK(3)];
        g_Self                = previous;
        previous->header.mode = 4;
    }
}
