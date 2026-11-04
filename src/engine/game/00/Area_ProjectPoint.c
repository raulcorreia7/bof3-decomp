#include "game_00.h"

MATCH void Area_ProjectPoint(s32* pos, long* screen_xy) {
    s16  vec[3];
    long p;
    long flag;

    vec[0] = (s16)(pos[0] >> 9) - 0x4000;
    vec[1] = (s16)(pos[1] >> 9) - 0x4000;
    vec[2] = (s16)(-(s16)FIELD(u16, pos, 0x0Au) / 2);
    RotTransPers((SVECTOR*)vec, screen_xy, &p, &flag);
}
