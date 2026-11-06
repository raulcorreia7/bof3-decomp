#include "game_00.h"

MATCH s32 func_801B8C64(s32 pos_x, s32 pos_y, s16* distance_out, s32 probe_mode) {
    s16 value;

    value         = Area_ReadStepHeight(pos_x, pos_y, probe_mode & 0xFF);
    *distance_out = value;
    if (SP_REF(u8, 0x0u) != 0 && value >= 0x41 && COORD_INT(g_Task->pos.z) < Area_ReadHeight(pos_x, pos_y)) {
        return 0;
    }
    *distance_out = Area_ReadHeight(pos_x, pos_y);
    return 1;
}
