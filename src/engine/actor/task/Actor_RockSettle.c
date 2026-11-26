#include "engine/game/00/game_00.h"

/* func_8019BBA4 */
/* Moves the rock on to its target cell edge, drops it to the ground and rests it; ends it when it lands blocked or too fast. */
MATCH void Actor_RockSettle(void) {
    s32 x;
    s32 y;
    s32 limit;
    s32 dist;

    x = SELF(Actor)->pos.x.fixed;
    y = SELF(Actor)->pos.y.fixed;
    if (SELF(Actor)->unk_18 != 0) {
        if (SELF(Actor)->vx != 0) {
            SELF(Actor)->pos.x.fixed = x + SELF(Actor)->vx;
            if (SELF(Actor)->vx > 0) {
                if (SELF(Actor)->unk_18 < SELF(Actor)->pos.x.fixed) {
                    SELF(Actor)->pos.x.fixed = SELF(Actor)->unk_18;
                    SELF(Actor)->unk_18      = 0;
                }
            } else {
                if (SELF(Actor)->pos.x.fixed < SELF(Actor)->unk_18) {
                    SELF(Actor)->pos.x.fixed = SELF(Actor)->unk_18;
                    SELF(Actor)->unk_18      = 0;
                }
            }
        } else {
            SELF(Actor)->pos.y.fixed = y + SELF(Actor)->vy;
            if (SELF(Actor)->vy > 0) {
                if (SELF(Actor)->unk_18 < SELF(Actor)->pos.y.fixed) {
                    SELF(Actor)->pos.y.fixed = SELF(Actor)->unk_18;
                    SELF(Actor)->unk_18      = 0;
                }
            } else {
                if (SELF(Actor)->pos.y.fixed < SELF(Actor)->unk_18) {
                    SELF(Actor)->pos.y.fixed = SELF(Actor)->unk_18;
                    SELF(Actor)->unk_18      = 0;
                }
            }
        }
    }
    dist = (s16)Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (dist < (s16)COORD_INT(SELF(Actor)->pos.z)) {
        SELF(Actor)->gravity = -8;
    } else {
        SELF(Actor)->gravity = 0;
        SELF(Actor)->vz      = 0;
    }
    SELF(Actor)->vz += SELF(Actor)->gravity;
    COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
    if ((Actor_RockHit() & BYTE_MASK) == 0) {
        if ((s16)COORD_INT(SELF(Actor)->pos.z) < dist) {
            COORD_INT(SELF(Actor)->pos.z) = (u16)Area_HeightSample(x, y);
            SELF(Actor)->vz               = 0;
            SELF(Actor)->gravity          = 0;
        }
        if ((SELF(Actor)->unk_18 == 0) && (SELF(Actor)->vz == 0)) {
            limit = SELF(Actor)->vx;
            limit = ABS(limit);
            if (limit >= 16385) {
                SELF(Actor)->header.mode = ACTOR_ROCK_MODE_END;
            } else {
                limit = SELF(Actor)->vy;
                limit = ABS(limit);
                if (limit >= 16385) {
                    SELF(Actor)->header.mode = ACTOR_ROCK_MODE_END;
                } else if ((Actor_RockIsCellBlocked(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) != 0) {
                    SELF(Actor)->header.mode = ACTOR_ROCK_MODE_END;
                } else {
                    SELF(Actor)->option_flags = 0;
                    SELF(Actor)->unk_0A       = 0;
                    Actor_RockClaimCell();
                    Script_Select(0);
                    SELF(Actor)->header.mode = ACTOR_ROCK_MODE_REST;
                }
            }
        }
        Script_AnimStepLoop();
        Area_SetDrawMode();
    }
}
