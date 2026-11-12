#include "game_00.h"

MATCH bool func_801C3E80(s32 pos_x, s32 pos_y, s32 probe_flag) {
    s32 i;

    i = 0;
    while (s_AreaProbeCellCodes[i] != 0xFF) {
        if ((func_801C472C(pos_x, pos_y, probe_flag, s_AreaProbeCellCodes[i], 1) & BYTE_MASK) == 0) {
            return 1;
        }
        i++;
    }
    if ((func_801C472C(pos_x, pos_y, probe_flag, 0x10, 0) & BYTE_MASK) == 0) {
        return 1;
    }
    if ((g_Game.current->status.field.flags_12C.u8_value & 0x1) == 0) {
        if ((func_801C472C(pos_x, pos_y, probe_flag, 0x11, 0) & BYTE_MASK) == 0) {
            return 1;
        }
    }
    if ((func_801C472C(pos_x, pos_y, probe_flag, 0x20, 0) & BYTE_MASK) == 0) {
        if ((func_801C472C(pos_x, pos_y, probe_flag, 0x21, 0) & BYTE_MASK) == 0) {
            return 1;
        }
    }
    if ((func_801C472C(pos_x, pos_y, probe_flag, 0xC0, 0) & BYTE_MASK) == 0) {
        if ((func_801C472C(pos_x, pos_y, probe_flag, 0xA0, 1) & BYTE_MASK) == 0) {
            return 1;
        }
    }
    return (func_801C472C(pos_x, pos_y, probe_flag, 0xA2, 0) & BYTE_MASK) == 0;
}
