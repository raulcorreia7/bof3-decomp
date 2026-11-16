#include "area102_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3194(void) {
    SVECTOR* vector;
    long     p;
    long     flag;

    vector            = D_1F800014;
    vector->vx        = (g_Task->pos.x.part.integer - 0x80) << 7;
    SP_REF(u16, 0x18) = -((s16)LOHU(g_Task->pos.z.part.integer) / 2);
    SP_REF(u16, 0x16) = (g_Task->pos.y.part.integer - 0x80) << 7;
    RotTransPers(vector, (long*)D_1F800034, &p, &flag);

    return (u16)(LOHU(D_1F800034[0]) + 0x14) < 0x169 && (u16)(LOHU(D_1F800034[1]) + 0x14) < 0x169;
}
#else
INCLUDE_ASM(func_801F3194);
#endif
