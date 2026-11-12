#include "game_00.h"

MATCH void func_801AFFD8(const void* world_position, void* screen_xy, void* projection) {
    VECTOR  projected;
    SVECTOR rot;
    long    flag;
    s16*    in;
    s16*    out;

    in     = (s16*)screen_xy;
    out    = (s16*)projection;
    rot.vx = ((FIELD(s32, world_position, 0x0u) >> 9) - 0x4000);
    rot.vy = ((FIELD(s32, world_position, 0x4u) >> 9) - 0x4000);
    rot.vz = (-FIELD(s16, world_position, 0xAu) / 2);
    RotTrans(&rot, &projected, &flag);
    out[0] = ((in[0] * 1000) / projected.vz);
    out[1] = ((in[1] * 1000) / projected.vz);
}
