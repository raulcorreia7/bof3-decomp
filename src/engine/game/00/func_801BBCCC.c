#include "game_00.h"

MATCH void func_801BBCCC(s16 from_x, s16 from_y, s16 to_x, s16 to_y) {
    SP_REF(u8, 0x1u) = func_801BB2B8(from_x, from_y, to_x, to_y);
    SP_REF(u8, 0x2u) = func_801BB2B8(from_x, FIELD(s16, g_Task, 0x3Au), to_x, COORD_INT(g_Task->pos.y));
    SP_REF(u8, 0x3u) =
        func_801BB2B8(from_x, (s16)(FIELD(u16, g_Task, 0x3Au) + 1), to_x, (s16)(FIELD(u16, g_Task, 0x3Au) + 1));
    SP_REF(u8, 0x4u) = func_801BB2B8(FIELD(s16, g_Task, 0x36u), from_y, COORD_INT(g_Task->pos.x), to_y);
    SP_REF(u8, 0x5u) =
        func_801BB2B8((s16)(FIELD(u16, g_Task, 0x36u) + 1), from_y, (s16)(FIELD(u16, g_Task, 0x36u) + 1), to_y);
    SP_REF(u8, 0x6u) =
        func_801BB2B8(from_x, (s16)(FIELD(u16, g_Task, 0x3Au) - 1), to_x, (s16)(FIELD(u16, g_Task, 0x3Au) - 1));
    SP_REF(u8, 0x7u) =
        func_801BB2B8((s16)(FIELD(u16, g_Task, 0x36u) - 1), from_y, (s16)(FIELD(u16, g_Task, 0x36u) - 1), to_y);
}
