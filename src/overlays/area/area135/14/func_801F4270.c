#include "area135_14.h"

MATCH void func_801F4270(void) {
    Actor* work;
    u8     index;
    s32    x;
    s32    y;

    work = &g_PartyActors[3];
    for (index = 0; index < 16; index++) {
        if (COORD_INT(work->pos.x) == D_801F6ABC[index].x && COORD_INT(work->pos.y) == D_801F6ABC[index].y) {
            if (D_801F6ABC[index].target_x != GAME_NONE && D_801F6ABC[index].target_y != GAME_NONE) {
                x = (D_801F6ABC[index].target_x << 16) | (D_801F6ABC[index].x_half ? 0x8000 : 0);
                y = (D_801F6ABC[index].target_y << 16) | (D_801F6ABC[index].y_half ? 0x8000 : 0);
                SELF(Actor)->active_flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                SELF(Actor)->header.step = 0;
                func_801ABD68(x, y, 16, g_ScriptState);
                g_ScriptState->steps   = 1;
                SELF(Actor)->direction = D_801F6ABC[index].direction;
                if (SELF(u8) == (u8*)&g_Game) {
                    g_AreaCamera.scroll_x.fixed = x;
                    g_AreaCamera.scroll_y.fixed = y;
                    g_AreaCameraSpeed           = 0x20;
                }
            } else {
                g_ScriptState->cursor -= 4;
                if (SELF(u8) == (u8*)&g_Game) {
                    g_ScriptVars[3] = 8;
                }
            }
        }
    }
}
