#include "engine/game/00/game_00.h"

/* func_8019CEDC */
/* Moves the block on by its velocity each frame and claims its new cells when it stops. */
MATCH void Actor_BlockSlide(void) {
    Actor* work;
    s32    moved;

    SELF(Actor)->timer = (SELF(Actor)->timer - 1);
    work               = SELF(Actor);
    work->pos.x.fixed += work->vx;
    moved             = work->pos.y.fixed + work->vy;
    work->pos.y.fixed = moved;
    if (work->timer == 0) {
        if (LOHU(g_GameAreaId) == AREA_ID_ANGEL_TOWER_LOWER) {
            if ((work->pos.x.fixed == TO_COORD(17) + COORD_HALF) && (moved == TO_COORD(74) + COORD_HALF)) {
                SYS_SetFlag(g_SceneEventFlags, 54);
            } else {
                SYS_ClearFlag(g_SceneEventFlags, 54);
            }
        }
        Actor_BlockClaimCells();
        SELF(Actor)->param.unk_0B = 0;
        SELF(Actor)->header.mode  = ACTOR_BLOCK_MODE_WAIT;
    }
    Actor_ProjectForDraw();
}
