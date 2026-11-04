#include "game_00.h"

MATCH void func_801B6BC8(void) {
    Actor* work;
    u8     sel;
    u8     flags;
    u8     delay;

    delay = g_GameState->countdown_119;
    if (delay != 0) {
        g_GameState->countdown_119 = (u8)(delay - 1);
        return;
    }
    sel = func_801A8D38(&g_GameState->flags_118, g_GameState->index_124);
    if (sel != GAME_NONE) {
        flags = g_GameState->flags_118;
        if (flags & 8) {
            g_GameState->flags_118 = (u8)(flags & 0xF7);
            if (!(D_80146871 & 0x40)) {
                g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            }
            Actor_RequestScript(g_SpadWork->direction_08);
            g_GameState->flags_12C.u8_value &= 0xFB;
            func_801C3204();
            g_SpadWork->unk_01 = 1;
            ACTOR_CLEAR_STATE();
            g_SpadWork->unk_03       = 0;
            g_SpadWork->unk_04       = 0;
            g_SpadWork->option_flags = 0;
            g_SpadWork->unk_06       = 0;
            return;
        }
        if (flags & 0x20) {
            if (!(g_SpadWork->option_flags & ACTOR_OPT_NO_SCRIPT_START)) {
                if (!(g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                    g_SpadWork->direction_08 = sel;
                    Actor_RequestScript(g_SpadWork->direction_08);
                }
                g_SpadWork->unk_03 = 3;
                return;
            }
        }
        flags = g_GameState->flags_118;
        if (flags & 2) {
            g_SpadWork->direction_08 = sel;
            func_801C2438();
            g_SpadWork->tint.signed_bytes.unk_5D = -0x40;
            g_SpadWork->tint.signed_bytes.unk_5E = -0x40;
            g_SpadWork->tint.signed_bytes.unk_5F = -0x40;
            g_SpadWork->tint.bytes.flags         = 1;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_03 = 4;
            return;
        }
        if (flags & 4) {
            g_SpadWork->direction_08 = sel;
            func_801C2438();
            g_SpadWork->tint.bytes.flags = 1;
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_03 = 5;
            return;
        }
        work = g_SpadWork;
        if (work->unk_09 != 0) {
            delay = g_GameState->wait_11F;
            if (delay != 0) {
                g_GameState->wait_11F = (u8)(delay - 1);
            }
            g_SpadWork->direction_08 = sel;
            g_SpadWork->unk_03       = 2;
            sel += 8;
            g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 - 1);
            func_801B0DFC();
        } else {
            work->direction_08 = sel;
            g_SpadWork->unk_03 = 1;
        }
        if ((g_GameState->flags_118 & 0x40) == 0) {
            Actor_RequestScript(sel);
        }
    }
}
