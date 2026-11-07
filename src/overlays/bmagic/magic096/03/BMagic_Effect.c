#include "magic096_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC84);

MATCH void func_801EEDD8(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x200);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEA0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEEE4(void) {
    BattleHandlerTable5 handlers = D_801EEC10;

    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF43C();
        func_801EF4FC();
        PopMatrix();
        Effect_SetActorMatrix();
        func_801EFB3C();
        func_801EFDF4();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFB8);

MATCH void func_801EF2CC(void) {
    g_Task->unk_09 += 2;
    g_Task->timer += 2;
    if (g_Task->unk_09 == D_801F0488[g_Task->unk_04]) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTickerAndStep.h"

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/Effect_CountDownAndFinish.h"

MATCH void func_801EF43C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = g_Task->unk_18;
    rot.vy = g_Task->unk_1C;
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF4FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFB3C);

INCLUDE_ASM(func_801EFDF4);

INCLUDE_ASM(func_801F0164);
