#include "engine/game/00/game_00.h"

/* func_801C2710 */
MATCH void Area_ScrollUpdateWalk(void) {
    Actor* work;
    Actor* state;
    s32    product;
    u8     index;

    work = SELF(Actor);
    if ((work->direction == 2) || (work->direction == 6)) {
        g_AreaCameraSpeed = 4;
    } else {
        g_AreaCameraSpeed = 8;
    }
    index                       = g_Game.current->u.field.counter.unsigned_value;
    product                     = g_AreaCameraSpeed * g_RouteSpeedScale[index];
    state                       = SELF(Actor);
    g_AreaCameraSpeed           = product;
    g_AreaCamera.scroll_x.fixed = state->pos.x.fixed + state->vx * state->timer;
    g_AreaCamera.scroll_y.fixed = state->pos.y.fixed + state->vy * state->timer;
    g_AreaCameraHeightDelta     = state->vz;
}
