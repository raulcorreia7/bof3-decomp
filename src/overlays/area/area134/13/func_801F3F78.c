#include "area134_13.h"
#include <rand.h>

MATCH void func_801F3F78(void) {
    u8*    state;
    Actor* actor;
    u8*    p;
    u8     val;

    state = &g_ScriptVars[1];
    if (*state == 0xFE) {
        func_80196070();
    }
    actor          = SELF(Actor);
    g_Game.current = (PartyMember*)&D_80146110;
    SELF_SET(&D_80146110);
    if (g_Game.members[2].pos.x.fixed > 0x33FFFF) {
        *state               = 0xFF;
        g_ScriptVars[2]      = 0;
        g_ScriptVars[3]      = 0;
        g_ScenarioState.step = 0x14;
        SELF_SET(actor);
        Actor_Clear();
        return;
    }
    SELF_SET(actor);
    if (*state == 0) {
        SELF(Actor)->timer       = D_801F5724[0x10 + (RANDOM_MASK(0xF))];
        SELF(Actor)->header.mode = 3;
        return;
    }
    if (g_PadStates[0].held == (PADLup | PADLright) || g_PadStates[0].held == (PADLright | PADLdown) || g_PadStates[0].held == PADLright) {
        p   = &g_ScriptVars[2];
        val = *p;
        *p  = val + 1;
        if (val < 0x10) {
            return;
        }
        *p = 0x80;
        Actor_Clear();
    }
}
