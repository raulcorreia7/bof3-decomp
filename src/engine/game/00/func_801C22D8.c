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
        work->direction_08 = FACING_NW;
    } else if (dx > 0 && dy > 0) {
        g_Task->direction_08 = FACING_SE;
    } else if (dx < 0 && dy > 0) {
        g_Task->direction_08 = FACING_SW;
    } else if (dx > 0 && dy < 0) {
        g_Task->direction_08 = FACING_NE;
    } else if (dx > 0 && dy == 0) {
        g_Task->direction_08 = FACING_E;
    } else if (dx < 0 && dy == 0) {
        g_Task->direction_08 = FACING_W;
    } else if (dx == 0) {
        if (dy > 0) {
            g_Task->direction_08 = FACING_S;
        } else if (dy < 0) {
            g_Task->direction_08 = FACING_N;
        }
    }
    Actor_RequestScript(g_Task->direction_08);
}
