#include "game_00.h"

MATCH void func_801C2BEC(void) {
    u16       flags;
    GameSlots table;
    u8        index;

    flags = g_Game.flags;

    table = D_80195FEC;
    if (flags & 0x400) {
        index = GAME_NONE;
    } else {
        if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x80, 0) & BYTE_MASK) {
            index = 0;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x81, 0) & BYTE_MASK) {
            index = 1;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x82, 0) & BYTE_MASK) {
            index = 2;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x83, 0) & BYTE_MASK) {
            index = 3;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x84, 0) & BYTE_MASK) {
            index = 4;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x85, 0) & BYTE_MASK) {
            index = 5;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x86, 0) & BYTE_MASK) {
            index = 6;
        } else if (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x87, 0) & BYTE_MASK) {
            index = 7;
        } else {
            index = (Game_TestMapCells(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, 0x88, 0) & BYTE_MASK) ? 8 : 0xFF;
        }
    }
    if (index != GAME_NONE) {
        Char_SetCharacterId(index);
        func_801C308C(table.cells[index]);
    }
}
