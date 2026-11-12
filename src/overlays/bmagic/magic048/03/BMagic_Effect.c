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

MATCH void func_801EF158(void) {
    s32 vec[4];
    u8  count;

    vec[0] = (g_Task->unk_0C >> 9) - 0x4000;
    vec[1] = (g_Task->unk_10 >> 9) - 0x4000;
    vec[2] = g_Task->unk_14 >> 1;
    /* The retail build passes the never-written slot after the vector. */
    func_800AF3A0(vec[0], vec[1], vec[2], vec[3], 0x10);
    g_Task->unk_09 = g_Task->unk_09 + 1;
    count          = g_Task->timer - 1;
    g_Task->timer  = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF234);

MATCH void func_801EF5C8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ratan2(g_Task->unk_10 - g_Task->pos.y.fixed, g_Task->unk_0C - g_Task->pos.x.fixed) & ANGLE_MASK;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF6A0);
