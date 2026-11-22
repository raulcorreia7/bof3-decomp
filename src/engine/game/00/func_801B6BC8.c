#include "game_00.h"

MATCH void func_801B6BC8(void) {
    Actor* work;
    u8     sel;
    u8     flags;
    u8     delay;

    delay = g_GameState->u.field.countdown;
    if (delay != 0) {
        g_GameState->u.field.countdown = (delay - 1);
        return;
    }
    sel = Script_Run(&g_GameState->u.field.flags, g_GameState->u.field.index);
    if (sel != GAME_NONE) {
        flags = g_GameState->u.field.flags;
        if (flags & 0x8) {
            g_GameState->u.field.flags = (flags & 0xF7);
            if (!(g_ScenarioState.flags_01 & SCENARIO_STATE_SCRIPT_ACTIVE)) {
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            Script_Request(g_Task->direction);
            g_Game.current->status.field.flags.unsigned_value &= 0xFB;
            func_801C3204();
            g_Task->header.mode = 1;
            ACTOR_CLEAR_STEP();
            g_Task->unk_03       = 0;
            g_Task->unk_04       = 0;
            g_Task->option_flags = 0;
            g_Task->unk_06       = 0;
            return;
        }
        if (flags & 0x20) {
            if (!(g_Task->option_flags & ACTOR_OPT_NO_SCRIPT_START)) {
                if (!(g_Task->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                    g_Task->direction = sel;
                    Script_Request(g_Task->direction);
                }
                g_Task->unk_03 = 3;
                return;
            }
        }
        flags = g_GameState->u.field.flags;
        if (flags & 0x2) {
            g_Task->direction = sel;
            Actor_SetSemiTransparent();
            g_Task->tint.steps.delta.r = -0x40;
            g_Task->tint.steps.delta.g = -0x40;
            g_Task->tint.steps.delta.b = -0x40;
            g_Task->tint.bytes.flags   = 1;
            Script_Request(g_Task->direction);
            g_Task->unk_03 = 4;
            return;
        }
        if (flags & 0x4) {
            g_Task->direction = sel;
            Actor_SetSemiTransparent();
            g_Task->tint.bytes.flags = 1;
            Script_Request(g_Task->direction);
            g_Task->unk_03 = 5;
            return;
        }
        work = g_Task;
        if (work->timer != 0) {
            delay = g_GameState->u.field.wait;
            if (delay != 0) {
                g_GameState->u.field.wait = (delay - 1);
            }
            g_Task->direction = sel;
            g_Task->unk_03    = 2;
            sel += 8;
            g_Task->timer = (g_Task->timer - 1);
            Actor_MovementUpdate();
        } else {
            work->direction = sel;
            g_Task->unk_03  = 1;
        }
        if ((g_Game.current->u.field.flags & 0x40) == 0) {
            Script_Request(sel);
        }
    }
}
