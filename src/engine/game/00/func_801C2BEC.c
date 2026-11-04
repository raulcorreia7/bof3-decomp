#include "game_00.h"

MATCH s32 func_801C2BEC(void) {
    u16       flags;
    GameSlots table;
    u8        index;

    flags = g_GameFlags;

    table = D_80195FEC;
    if (flags & 0x400) {
        index = 0xFF;
    } else {
        if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x80, 0) & BYTE_MASK) {
            index = 0;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x81, 0) &
                   BYTE_MASK) {
            index = 1;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x82, 0) &
                   BYTE_MASK) {
            index = 2;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x83, 0) &
                   BYTE_MASK) {
            index = 3;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x84, 0) &
                   BYTE_MASK) {
            index = 4;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x85, 0) &
                   BYTE_MASK) {
            index = 5;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x86, 0) &
                   BYTE_MASK) {
            index = 6;
        } else if (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x87, 0) &
                   BYTE_MASK) {
            index = 7;
        } else {
            index = (func_801C39D8(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, 0x88, 0) &
                     BYTE_MASK)
                        ? 8
                        : 0xFF;
        }
    }
    if (index != GAME_NONE) {
        func_801C2E34(index);
        func_801C308C(table.cells[index]);
    }
}
