#include "game_00.h"

MATCH void Area_ProjectPoint(s32* pos, s16* screen_xy) {
    SVECTOR vec;
    long    p;
    long    flag;

    vec.vx = (pos[0] >> 9) - 0x4000;
    vec.vy = (pos[1] >> 9) - 0x4000;
    vec.vz = (-(s16)FIELD(u16, pos, 0x0Au) / 2);
    RotTransPers(&vec, (long*)screen_xy, &p, &flag);
}
