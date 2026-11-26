#include "engine/game/00/game_00.h"

/* func_801B9100 */
/* Spins the actor as it sinks and requests the area change once it is far below the ground. */
MATCH void Party_FallThroughSpin(void) {
    Actor* work;
    s32    adjustment;
    s16    distance;

    work            = TASK(Actor);
    work->direction = (work->direction + 1) & 0x7;
    adjustment      = work->vz - 8;
    COORD_INT(work->pos.z) += adjustment;
    work->vz = adjustment;
    Script_Request(TASK(Actor)->direction);
    distance = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    if (distance - (s16)COORD_INT(TASK(Actor)->pos.z) >= 257) {
        u8* state = &g_GameStateIndex;

        if (*state != GAME_REQUEST_AREA_CHANGE) {
            *state = GAME_REQUEST_AREA_CHANGE;
            g_AreaWalkFlags |= 0x200;
        }
    }
}
