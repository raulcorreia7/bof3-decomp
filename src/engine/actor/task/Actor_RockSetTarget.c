#include "engine/game/00/game_00.h"

/* func_8019C124 */
/* Sets the cell edge the rock rolls on to along its velocity and enters the settle mode. */
MATCH void Actor_RockSetTarget(s32 step_byte) {
    Actor* work;
    s32    vel;

    work = SELF(Actor);
    if (COORD_FRAC(work->pos.x) != 0) {
        vel = work->vx;
        if (vel > 0) {
            if ((step_byte & BYTE_MASK) == 0) {
                work->unk_18 = (work->pos.x.fixed + TO_COORD(1)) & 0xFFFF0000;
                goto set_state;
            }
        } else if (vel < 0) {
            /* keep the current tile */
        } else {
            goto set_state;
        }
        work->unk_18 = work->pos.x.fixed & 0xFFFF0000;
    } else if (COORD_FRAC(work->pos.y) != 0) {
        vel = work->vy;
        if (vel > 0) {
            if ((step_byte & BYTE_MASK) == 0) {
                work->unk_18 = (work->pos.y.fixed + TO_COORD(1)) & 0xFFFF0000;
                goto set_state;
            }
        } else if (vel < 0) {
            /* keep the current tile */
        } else {
            goto set_state;
        }
        work->unk_18 = work->pos.y.fixed & 0xFFFF0000;
    } else {
        return;
    }
set_state:
    SELF(Actor)->header.mode = ACTOR_ROCK_MODE_SETTLE;
}
