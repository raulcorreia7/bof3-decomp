#include "magic048_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_CountDownTimerQueueFx.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE70 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEB4(void) {
    SYS_DISPATCH_BYTE(D_801EF81C, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        func_801EF5C8();
        func_801EF234();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEF3C);

INCLUDE_ASM(func_801EF05C);

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF234);

MATCH void func_801EF5C8(void) {
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;
    PartyMember* work;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ratan2(work->unk_10 - work->pos.y.fixed, work->unk_0C - work->pos.x.fixed) & 0xFFF;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF6A0);
