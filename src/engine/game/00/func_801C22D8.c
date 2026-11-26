#include "game_00.h"

MATCH void func_801C22D8(void) {
    s32    dx;
    s32    dy;
    Actor* work;

    if (g_GameStateIndex != GAME_REQUEST_SCENE_CAMERA) {
        SELF(Actor)->header.mode = 1;
        return;
    }
    work = SELF(Actor);
    dx   = g_Game.base_x.fixed - work->pos.x.fixed;
    dy   = g_Game.base_y.fixed - work->pos.y.fixed;
    if (dx < 0 && dy < 0) {
        work->direction = FACING_UP_LEFT;
    } else if (dx > 0 && dy > 0) {
        SELF(Actor)->direction = FACING_DOWN_RIGHT;
    } else if (dx < 0 && dy > 0) {
        SELF(Actor)->direction = FACING_DOWN_LEFT;
    } else if (dx > 0 && dy < 0) {
        SELF(Actor)->direction = FACING_UP_RIGHT;
    } else if (dx > 0 && dy == 0) {
        SELF(Actor)->direction = FACING_RIGHT;
    } else if (dx < 0 && dy == 0) {
        SELF(Actor)->direction = FACING_LEFT;
    } else if (dx == 0) {
        if (dy > 0) {
            SELF(Actor)->direction = FACING_DOWN;
        } else if (dy < 0) {
            SELF(Actor)->direction = FACING_UP;
        }
    }
    Script_Request(SELF(Actor)->direction);
}
