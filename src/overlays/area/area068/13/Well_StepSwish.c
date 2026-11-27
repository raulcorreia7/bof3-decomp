#include "area068_13.h"

/* func_801F3304 */
MATCH void Well_StepSwish(void) {
    Actor* work;

    if (++g_WellSwishStep >= WELL_SWISH_STEPS) {
        work        = SELF(Actor);
        g_GameState = g_Game.members;
        SELF_SET(g_Game.members);
        g_Game.members[0].pos.y.fixed &= 0xFFFFF000;
        g_Game.members[0].pos.x.fixed &= 0xFFFFF000;
        g_Self            = work;
        work->header.mode = WELL_MODE_RAISE_BEGIN;
        g_WellPressCount  = 0;
        g_WellSwishStep   = 0;
    } else {
        switch (g_WellSwishButtons) {
            case PADLup:
            case (PADLup | PADLright):
                work        = SELF(Actor);
                g_GameState = g_Game.members;
                SELF_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed += 0x800;
                g_Self = work;
                break;
            case PADLright:
            case (PADLdown | PADLright):
                work        = SELF(Actor);
                g_GameState = g_Game.members;
                SELF_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed -= 0x800;
                g_Self = work;
                break;
            case PADLdown:
            case (PADLleft | PADLdown):
                work        = SELF(Actor);
                g_GameState = g_Game.members;
                SELF_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed -= 0x800;
                g_Self = work;
                break;
            case PADLleft:
            case (PADLleft | PADLup):
                work        = SELF(Actor);
                g_GameState = g_Game.members;
                SELF_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed += 0x800;
                g_Self = work;
                break;
        }
        SELF(Actor)->header.mode = WELL_MODE_SWISH_INPUT;
    }
}
