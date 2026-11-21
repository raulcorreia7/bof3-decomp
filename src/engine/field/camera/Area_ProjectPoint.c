#include "engine/game/00/game_00.h"

MATCH void Area_ProjectPoint(s32* pos, DVECTOR* screen_xy) {
    SVECTOR vec;
    long    p;
    long    flag;

    setVector(&vec, (pos[0] >> 9) - 0x4000, (pos[1] >> 9) - 0x4000, (-(s16)FIELD(u16, pos, 0x0Au) / 2));
    RotTransPers(&vec, (long*)screen_xy, &p, &flag);
}
