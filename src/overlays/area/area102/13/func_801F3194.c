#include "area102_13.h"

MATCH s32 func_801F3194(void) {
    s32  vx;
    s32  vy;
    s16  vz;
    long depth;
    long flag;

    vx = (COORD_INT(SELF(Actor)->pos.x) - 0x80) << 7;
    vy = (COORD_INT(SELF(Actor)->pos.y) - 0x80) << 7;
    vz = -(COORD_INT(SELF(Actor)->pos.z) / 2);
    setVector(&g_ScratchPadVectors[0], vx, vy, vz);
    RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
    if ((u16)(D_1F800034[0] + 0x14) >= 0x169 || (u16)(D_1F800034[1] + 0x14) >= 0x169) {
        return 0;
    }
    return 1;
}
