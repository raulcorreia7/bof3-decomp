#include "area068_13.h"

MATCH void func_801F2C6C(void) {
    Actor* task;

    task = SELF(Actor);
    if (g_ScriptVars[1] != 0) {
        g_GameState = g_Game.members;
        SELF_SET(g_Game.members);
        g_Game.members[0].u.turn.command.target |= 0x40;
        Script_Select(0x6FU);
        g_Self = task;
        g_Game.members[0].unk_07 &= 0x11;
        task->header.mode = 2;
    }
}
