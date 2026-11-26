#include "engine/game/00/game_00.h"

/* func_8019BBA4 */
/* Moves the rock on to its target cell edge, drops it to the ground and rests it; ends it when it lands blocked or too fast. */
MATCH void Actor_RockSettle(void) {
    s32 x;
    s32 y;
    s32 limit;
    s32 dist;

    x = TASK(Actor)->pos.x.fixed;
    y = TASK(Actor)->pos.y.fixed;
    if (TASK(Actor)->unk_18 != 0) {
        if (TASK(Actor)->vx != 0) {
            TASK(Actor)->pos.x.fixed = x + TASK(Actor)->vx;
            if (TASK(Actor)->vx > 0) {
                if (TASK(Actor)->unk_18 < TASK(Actor)->pos.x.fixed) {
                    TASK(Actor)->pos.x.fixed = TASK(Actor)->unk_18;
                    TASK(Actor)->unk_18      = 0;
                }
            } else {
                if (TASK(Actor)->pos.x.fixed < TASK(Actor)->unk_18) {
                    TASK(Actor)->pos.x.fixed = TASK(Actor)->unk_18;
                    TASK(Actor)->unk_18      = 0;
                }
            }
        } else {
            TASK(Actor)->pos.y.fixed = y + TASK(Actor)->vy;
            if (TASK(Actor)->vy > 0) {
                if (TASK(Actor)->unk_18 < TASK(Actor)->pos.y.fixed) {
                    TASK(Actor)->pos.y.fixed = TASK(Actor)->unk_18;
                    TASK(Actor)->unk_18      = 0;
                }
            } else {
                if (TASK(Actor)->pos.y.fixed < TASK(Actor)->unk_18) {
                    TASK(Actor)->pos.y.fixed = TASK(Actor)->unk_18;
                    TASK(Actor)->unk_18      = 0;
                }
            }
        }
    }
    dist = (s16)Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    if (dist < (s16)COORD_INT(TASK(Actor)->pos.z)) {
        TASK(Actor)->gravity = -8;
    } else {
        TASK(Actor)->gravity = 0;
        TASK(Actor)->vz      = 0;
    }
    TASK(Actor)->vz += TASK(Actor)->gravity;
    COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
    if ((Actor_RockHit() & BYTE_MASK) == 0) {
        if ((s16)COORD_INT(TASK(Actor)->pos.z) < dist) {
            COORD_INT(TASK(Actor)->pos.z) = (u16)Area_HeightSample(x, y);
            TASK(Actor)->vz               = 0;
            TASK(Actor)->gravity          = 0;
        }
        if ((TASK(Actor)->unk_18 == 0) && (TASK(Actor)->vz == 0)) {
            limit = TASK(Actor)->vx;
            limit = ABS(limit);
            if (limit >= 16385) {
                TASK(Actor)->header.mode = ACTOR_ROCK_MODE_END;
            } else {
                limit = TASK(Actor)->vy;
                limit = ABS(limit);
                if (limit >= 16385) {
                    TASK(Actor)->header.mode = ACTOR_ROCK_MODE_END;
                } else if ((Actor_RockIsCellBlocked(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y)) & BYTE_MASK) != 0) {
                    TASK(Actor)->header.mode = ACTOR_ROCK_MODE_END;
                } else {
                    TASK(Actor)->option_flags = 0;
                    TASK(Actor)->unk_0A       = 0;
                    Actor_RockClaimCell();
                    Script_Select(0);
                    TASK(Actor)->header.mode = ACTOR_ROCK_MODE_REST;
                }
            }
        }
        Script_AnimStepLoop();
        Area_SetDrawMode();
    }
}
