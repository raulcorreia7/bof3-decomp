#include "game_00.h"

MATCH void func_801C22D8(void) {
    s32    dx;
    s32    dy;
    Actor* work;

    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        g_Task->mode = 1;
        return;
    }
    work = g_Task;
    dx   = D_801462A0 - work->x.fixed;
    dy   = D_801462A4 - work->y.fixed;
    if (dx < 0 && dy < 0) {
        work->direction_08 = 0;
    } else if (dx > 0 && dy > 0) {
        g_Task->direction_08 = 4;
    } else if (dx < 0 && dy > 0) {
        g_Task->direction_08 = 6;
    } else if (dx > 0 && dy < 0) {
        g_Task->direction_08 = 2;
    } else if (dx > 0 && dy == 0) {
        g_Task->direction_08 = 3;
    } else if (dx < 0 && dy == 0) {
        g_Task->direction_08 = 7;
    } else if (dx == 0) {
        if (dy > 0) {
            g_Task->direction_08 = 5;
        } else if (dy < 0) {
            g_Task->direction_08 = 1;
        }
    }
    Actor_RequestScript(g_Task->direction_08);
}
