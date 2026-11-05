#include "game_00.h"

MATCH u16* func_801C71C4(u16* out, s32 pos_x, s32 pos_y, s32 view_height) {
    SVECTOR input;
    VECTOR  projection;

    input.vx = (pos_x >> 9) - 0x4000;
    input.vy = (pos_y >> 9) - 0x4000;
    input.vz = (-(view_height >> 0x10) / 2);
    RotTransPers(&input, &projection.vx, &projection.vz, &projection.pad);
    memcpy(out, &projection.vx, sizeof(projection.vx));
    return out;
}
