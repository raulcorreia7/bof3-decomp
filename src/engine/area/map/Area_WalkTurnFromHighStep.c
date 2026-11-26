#include "engine/game/00/game_00.h"

/* Probes the step height along the actor's tile on each axis and turns the facing away from a step that is too high. */
/* func_801BB9B4 */
MATCH void Area_WalkTurnFromHighStep(s16 probe_x, s16 probe_y) {
    u8 route;

    if (TASK(Actor)->direction & 0x1) {
        return;
    }
    if (Area_IsStepTooHigh(probe_x, probe_x, COORD_INT(TASK(Actor)->pos.y), (s16)(COORD_INT(TASK(Actor)->pos.y) + 1), 1) & BYTE_MASK) {
        Actor_SnapFacing(4, 6, 5);
    }
    if (TASK(Actor)->direction & 0x1) {
        return;
    }
    if (!(TASK(Actor)->direction & 0x4)) {
        if (Area_IsStepTooHigh(probe_x, probe_x, COORD_INT(TASK(Actor)->pos.y), probe_y, 1) & BYTE_MASK) {
            Actor_SnapFacing(4, 6, 5);
        }
    } else {
        if (Area_IsStepTooHigh(probe_x, probe_x, probe_y, (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1), 1) & BYTE_MASK) {
            Actor_SnapFacing(4, 6, 5);
        }
    }
    if (TASK(Actor)->direction & 0x1) {
        return;
    }
    if (Area_IsStepTooHigh(COORD_INT(TASK(Actor)->pos.x), (s16)(COORD_INT(TASK(Actor)->pos.x) + 1), probe_y, probe_y, 3) & BYTE_MASK) {
        Actor_SnapFacing(2, 4, 3);
    }
    route = TASK(Actor)->direction;
    if (route & 0x1) {
        return;
    }
    if ((route == FACING_UP_LEFT) || (route == FACING_DOWN_LEFT)) {
        if (Area_IsStepTooHigh(COORD_INT(TASK(Actor)->pos.x), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            Actor_SnapFacing(2, 4, 3);
        }
    } else {
        if (Area_IsStepTooHigh((s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            Actor_SnapFacing(2, 4, 3);
        }
    }
}
