#include "area102_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3194(void) {
    s32  vx;
    s32  vy;
    s32  vz;
    long depth;
    long flag;
    s16* screen;

    screen           = D_1F800034;
    vz               = -(COORD_INT(g_Task->pos.z) / 2);
    vx               = (COORD_INT(g_Task->pos.x) - 0x80) << 7;
    vy               = (COORD_INT(g_Task->pos.y) - 0x80) << 7;
    D_1F800014[0].vx = vx;
    D_1F800018       = vz;
    D_1F800016       = vy;
    RotTransPers(D_1F800014, (long*)screen, &depth, &flag);
    if ((u16)(screen[0] + 0x14) < 0x169) {
        if ((u16)(D_1F800034[1] + 0x14) >= 0x169) {
            return 0;
        }
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F3194);
#endif
