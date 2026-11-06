#include "game_00.h"

MATCH s32 func_801C3E40(s32 pos_x, s32 pos_y, s32 probe_flag, s16 probe_range) {
    if ((probe_flag & BYTE_MASK) == 0) {
        return func_801C4040(pos_x, pos_y, probe_range) & BYTE_MASK;
    }
    return func_801C41D0(pos_x, pos_y, probe_range) & BYTE_MASK;
}
