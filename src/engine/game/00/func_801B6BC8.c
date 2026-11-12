#include "game_00.h"

MATCH void func_801B6BC8(void) {
    Actor* work;
    u8     sel;
    u8     flags;
    u8     delay;

    delay = g_GameState->u.field.countdown_119;
    if (delay != 0) {
        g_GameState->u.field.countdown_119 = (delay - 1);
        return;
    }
    sel = func_801A8D38(&g_GameState->u.field.flags_118, g_GameState->u.field.index_124);
    if (sel != GAME_NONE) {
        flags = g_GameState->u.field.flags_118;
        if (flags & 0x8) {
            g_GameState->u.field.flags_118 = (flags & 0xF7);
            if (!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE)) {
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            Actor_RequestScript(g_Task->direction_08);
            g_Game.current->status.field.flags_12C.u8_value &= 0xFB;
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
                    g_Task->direction_08 = sel;
                    Actor_RequestScript(g_Task->direction_08);
                }
                g_Task->unk_03 = 3;
                return;
            }
        }
        flags = g_GameState->u.field.flags_118;
        if (flags & 0x2) {
            g_Task->direction_08 = sel;
            func_801C2438();
            g_Task->tint.signed_bytes.unk_5D = -0x40;
            g_Task->tint.signed_bytes.unk_5E = -0x40;
            g_Task->tint.signed_bytes.unk_5F = -0x40;
            g_Task->tint.bytes.flags         = 1;
            Actor_RequestScript(g_Task->direction_08);
            g_Task->unk_03 = 4;
            return;
        }
        if (flags & 0x4) {
            g_Task->direction_08 = sel;
            func_801C2438();
            g_Task->tint.bytes.flags = 1;
            Actor_RequestScript(g_Task->direction_08);
            g_Task->unk_03 = 5;
            return;
        }
        work = g_Task;
        if (work->timer != 0) {
            delay = g_GameState->u.field.wait_11F;
            if (delay != 0) {
                g_GameState->u.field.wait_11F = (delay - 1);
            }
            g_Task->direction_08 = sel;
            g_Task->unk_03       = 2;
            sel += 8;
            g_Task->timer = (g_Task->timer - 1);
            func_801B0DFC();
        } else {
            work->direction_08 = sel;
            g_Task->unk_03     = 1;
        }
        if ((g_Game.current->u.field.flags_118 & 0x40) == 0) {
            Actor_RequestScript(sel);
        }
    }
}
