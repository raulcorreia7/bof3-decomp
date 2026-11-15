#include "area102_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3194(void) {
    u16  zi;
    long p;
    long flag;

    zi = *(u16*)&COORD_INT(g_Task->pos.z);
    setVector(D_1F800014, (FIX_INT(g_Task->pos.x.fixed) - 0x80) << 7, (FIX_INT(g_Task->pos.y.fixed) - 0x80) << 7, -(s16)zi / 2);
    RotTransPers(D_1F800014, (long*)((u16*)D_1F800034), &p, &flag);
    if (((u32)(((u16*)D_1F800034)[0] + 0x14) & HALF_MASK) >= 0x169) {
        return 0;
    }
    if (((u32)(((u16*)D_1F800034)[1] + 0x14) & HALF_MASK) >= 0x169) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM(func_801F3194);
#endif
