#include "area134_13.h"

MATCH void func_801F40C8(void) {
    Actor* actor;
    u8*    state;

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
        func_80196070();
    } else {
        SELF_SET(actor);
        if (SELF(Actor)->timer-- == 0) {
            g_ScenarioState.timer_06 = 0;
            SELF(Actor)->header.mode = 1;
        }
    }
}
