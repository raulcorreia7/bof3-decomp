#include "area134_13.h"

MATCH void func_801F3440(void) {
    Actor* actor;
    u8     step;

    actor       = SELF(Actor);
    g_GameState = &g_Game.members[2];
    SELF_SET(&g_Game.members[2].header.flags);
    if (g_Game.members[2].pos.x.fixed > 0x33FFFF) {
        g_ScriptVars[1] = 0xFF;
        step            = 0x14;
    } else {
        g_ScriptVars[1] = 0xFE;
        step            = 0x1E;
    }
    g_ScriptVars[2]      = 0;
    g_ScriptVars[3]      = 0;
    g_ScenarioState.step = step;
    SELF_SET(actor);
    func_80196070();
}
