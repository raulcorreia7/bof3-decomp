#include "engine/game/00/game_00.h"

/* func_801B6BC8 */
/* Reads the next script record and picks the sub-step it asks for. */
MATCH void Party_ScriptWalkRead(void) {
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
            Script_Request(TASK(Actor)->direction);
            g_Game.current->status.field.flags.unsigned_value &= 0xFB;
            func_801C3204();
            TASK(Actor)->header.mode = 1;
            ACTOR_CLEAR_STEP();
            TASK(Actor)->unk_03       = 0;
            TASK(Actor)->unk_04       = 0;
            TASK(Actor)->option_flags = 0;
            TASK(Actor)->unk_06       = 0;
            return;
        }
        if (flags & 0x20) {
            if (!(TASK(Actor)->option_flags & ACTOR_OPT_NO_SCRIPT_START)) {
                if (!(TASK(Actor)->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                    TASK(Actor)->direction = sel;
                    Script_Request(TASK(Actor)->direction);
                }
                TASK(Actor)->unk_03 = 3;
                return;
            }
        }
        flags = g_GameState->u.field.flags;
        if (flags & 0x2) {
            TASK(Actor)->direction = sel;
            Actor_SetSemiTransparent();
            TASK(Actor)->tint.steps.delta.r = -0x40;
            TASK(Actor)->tint.steps.delta.g = -0x40;
            TASK(Actor)->tint.steps.delta.b = -0x40;
            TASK(Actor)->tint.bytes.flags   = 1;
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->unk_03 = 4;
            return;
        }
        if (flags & 0x4) {
            TASK(Actor)->direction = sel;
            Actor_SetSemiTransparent();
            TASK(Actor)->tint.bytes.flags = 1;
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->unk_03 = 5;
            return;
        }
        work = TASK(Actor);
        if (work->timer != 0) {
            delay = g_GameState->u.field.wait;
            if (delay != 0) {
                g_GameState->u.field.wait = (delay - 1);
            }
            TASK(Actor)->direction = sel;
            TASK(Actor)->unk_03    = 2;
            sel += 8;
            TASK(Actor)->timer = (TASK(Actor)->timer - 1);
            Actor_MovementUpdate();
        } else {
            work->direction     = sel;
            TASK(Actor)->unk_03 = 1;
        }
        if ((g_Game.current->u.field.flags & 0x40) == 0) {
            Script_Request(sel);
        }
    }
}
