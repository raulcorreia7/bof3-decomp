#include "game_00.h"

/* Two probe passes over the work area's tile. */
MATCH void func_801BB9B4(s16 probe_x, s16 probe_y) {
    u8 route;

    if (g_Task->direction_08 & 1) {
        return;
    }
    if (func_801BB86C(probe_x, probe_x, COORD_INT(g_Task->pos.y), (s16)(COORD_INT(g_Task->pos.y) + 1), 1) & BYTE_MASK) {
        func_801BB8E8(4, 6, 5);
    }
    if (g_Task->direction_08 & 1) {
        return;
    }
    if (!(g_Task->direction_08 & 4)) {
        if (func_801BB86C(probe_x, probe_x, COORD_INT(g_Task->pos.y), probe_y, 1) & BYTE_MASK) {
            func_801BB8E8(4, 6, 5);
        }
    } else {
        if (func_801BB86C(probe_x, probe_x, probe_y, (s16)((u16)COORD_INT(g_Task->pos.y) + 1), 1) & BYTE_MASK) {
            func_801BB8E8(4, 6, 5);
        }
    }
    if (g_Task->direction_08 & 1) {
        return;
    }
    if (func_801BB86C(COORD_INT(g_Task->pos.x), (s16)(COORD_INT(g_Task->pos.x) + 1), probe_y, probe_y, 3) & BYTE_MASK) {
        func_801BB8E8(2, 4, 3);
    }
    route = g_Task->direction_08;
    if (route & 1) {
        return;
    }
    if ((route == 0) || (route == 6)) {
        if (func_801BB86C(COORD_INT(g_Task->pos.x), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            func_801BB8E8(2, 4, 3);
        }
    } else {
        if (func_801BB86C((s16)((u16)COORD_INT(g_Task->pos.x) + 1), probe_x, probe_y, probe_y, 3) & BYTE_MASK) {
            func_801BB8E8(2, 4, 3);
        }
    }
}
