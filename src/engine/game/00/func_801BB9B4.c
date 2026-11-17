#include "game_00.h"

/* Two probe passes over the work area's tile: the first walks the coordinate
 * pair's second half (Y) toward probe_y with mode 1, the second walks the first
 * half (X) toward probe_x with mode 3. Each pass first probes the step from the
 * current tile and then the step from that edge toward the target, rewriting
 * route_index_08 whenever a probe's route level passes.
 * halves, the stepped edge and the coordinates in probe_x/probe_y, then advances the
 * route byte through Actor_SnapFacing. Bit 0 of route_index_08 stops every probe
 * and bit 2 selects the far edge of the pair.
 */
MATCH void func_801BB9B4(s16 probe_x, s16 probe_y) {
    u8 route;

    if (g_Task->direction & 0x1) {
        return;
    }
    if (Area_IsStepTooHigh(probe_x, probe_x, COORD_INT(g_Task->pos.y), (s16)(COORD_INT(g_Task->pos.y) + 1), 1) & BYTE_MASK) {
        Actor_SnapFacing(4, 6, 5);
    }
    if (g_Task->direction & 0x1) {
        return;
    }
    if (!(g_Task->direction & 0x4)) {
        if (Area_IsStepTooHigh(probe_x, probe_x, COORD_INT(g_Task->pos.y), probe_y, 1) & BYTE_MASK) {
            Actor_SnapFacing(4, 6, 5);
        }
    } else {
        if (Area_IsStepTooHigh(probe_x, probe_x, probe_y, (s16)((u16)COORD_INT(g_Task->pos.y) + 1), 1) & BYTE_MASK) {
            Actor_SnapFacing(4, 6, 5);
        }
    }
    if (g_Task->direction & 0x1) {
        return;
    }
    if (Area_IsStepTooHigh(COORD_INT(g_Task->pos.x), (s16)(COORD_INT(g_Task->pos.x) + 1), probe_y, probe_y, 3) & BYTE_MASK) {
        Actor_SnapFacing(2, 4, 3);
    }
    route = g_Task->direction;
    if (route & 0x1) {
        return;
    }
    if ((route == FACING_UP_LEFT) || (route == FACING_DOWN_LEFT)) {
        if (Area_IsStepTooHigh(COORD_INT(g_Task->pos.x), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            Actor_SnapFacing(2, 4, 3);
        }
    } else {
        if (Area_IsStepTooHigh((s16)((u16)COORD_INT(g_Task->pos.x) + 1), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            Actor_SnapFacing(2, 4, 3);
        }
    }
}
