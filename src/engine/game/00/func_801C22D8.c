#include "game_00.h"

MATCH void func_801C22D8(void) {
    s32    dx;
    s32    dy;
    Actor* work;

    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        g_Task->header.mode = 1;
        return;
    }
    work = g_Task;
    dx   = D_801462A0 - work->pos.x.fixed;
    dy   = D_801462A4 - work->pos.y.fixed;
    if (dx < 0 && dy < 0) {
        work->direction_08 = FACING_UP_LEFT;
    } else if (dx > 0 && dy > 0) {
        g_Task->direction_08 = FACING_DOWN_RIGHT;
    } else if (dx < 0 && dy > 0) {
        g_Task->direction_08 = FACING_DOWN_LEFT;
    } else if (dx > 0 && dy < 0) {
        g_Task->direction_08 = FACING_UP_RIGHT;
    } else if (dx > 0 && dy == 0) {
        g_Task->direction_08 = FACING_RIGHT;
    } else if (dx < 0 && dy == 0) {
        g_Task->direction_08 = FACING_LEFT;
    } else if (dx == 0) {
        if (dy > 0) {
            g_Task->direction_08 = FACING_DOWN;
        } else if (dy < 0) {
            g_Task->direction_08 = FACING_UP;
        }
    }
    Actor_RequestScript(g_Task->direction_08);
}
