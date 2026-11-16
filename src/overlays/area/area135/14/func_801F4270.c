#define FAKE_DECL_TASK_VOLATILE
#include "area135_14.h"

MATCH void func_801F4270(void) {
    Actor* work;
    u8     index;
    s32    x;
    s32    y;

    work = &D_80147A58[3];
    for (index = 0; index < 16; index++) {
        if (COORD_INT(work->pos.x) == D_801F6ABC[index].x && COORD_INT(work->pos.y) == D_801F6ABC[index].y) {
            if (D_801F6ABC[index].target_x != GAME_NONE && D_801F6ABC[index].target_y != GAME_NONE) {
                x = (D_801F6ABC[index].target_x << 16) | (D_801F6ABC[index].x_half ? 0x8000 : 0);
                y = (D_801F6ABC[index].target_y << 16) | (D_801F6ABC[index].y_half ? 0x8000 : 0);
                g_Task->active_flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                g_Task->header.step = 0;
                func_801ABD68(x, y, 16, g_ScriptState);
                g_ScriptState->unk_07 = 1;
                g_Task->direction_08  = D_801F6ABC[index].direction;
                if ((u8*)g_Task == (u8*)&g_Game) {
                    g_AreaScrollTargetX = x;
                    g_AreaScrollTargetY = y;
                    g_AreaCameraStep    = 0x20;
                }
            } else {
                g_ScriptState->cursor -= 4;
                if ((u8*)g_Task == (u8*)&g_Game) {
                    g_ScriptVars[3] = 8;
                }
            }
        }
    }
}
