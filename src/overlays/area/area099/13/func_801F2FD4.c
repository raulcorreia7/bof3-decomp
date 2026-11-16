#include "area099_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FD4(void) {
    Actor* scratch;
    Actor* check;
    u8     mode;
    s32    x;
    s32    step;
    s32    y;
    s32    vy;
    s32    vz;

    scratch              = g_Task;
    x                    = scratch->pos.x.fixed;
    mode                 = scratch->unk_0A;
    step                 = scratch->vx;
    vy                   = scratch->vy;
    scratch->pos.x.fixed = x + step;
    y                    = scratch->pos.y.fixed;
    vz                   = scratch->vz;
    scratch->unk_0A      = mode - 1;
    scratch->pos.y.fixed = y + vy;
    COORD_INT(scratch->pos.z) += scratch->vz >> 8;
    scratch->vz = vz - 0x700;
    if (vz > 0 && g_Task->vz < 0) {
        Actor_RequestScript(0x51);
    }
    check = g_Task;
    if (check->unk_0A == 0) {
        check->unk_04 = 0;
    } else {
        g_Game.current->u.field.unk_122 -= 2;
    }
}
#else
INCLUDE_ASM(func_801F2FD4);
#endif
