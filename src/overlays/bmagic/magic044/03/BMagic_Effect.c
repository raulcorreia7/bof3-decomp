#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE00(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

INCLUDE_ASM(func_801EEE44);

INCLUDE_ASM(func_801EEEFC);

INCLUDE_ASM(func_801EF138);

INCLUDE_ASM(func_801EF320);

MATCH void func_801EF478(void) {
    u8 timer;

    func_801F0390();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4E0);

INCLUDE_ASM(func_801EFA4C);

MATCH void func_801F02A0(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F0A38)
    D_801F0A38[g_Task->unk_04][g_Task->param.unk_0B].x = g_Task->unk_2E.half;
    D_801F0A38[g_Task->unk_04][g_Task->param.unk_0B].y = g_Task->unk_30.half;
}

MATCH void func_801F0390(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(D_801F0A38)
    D_801F0A38[g_Task->unk_04][g_Task->param.unk_0B].x = -1;
    D_801F0A38[g_Task->unk_04][g_Task->param.unk_0B].y = -1;
}

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F06D8();
    }
}

MATCH void func_801F04F0(void) {
    func_800AF764();
    g_Task->unk_30.half += 8;
    g_Task->unk_5D = (rand() & 3) + 1;
    g_Task->unk_5E = (rand() & 3) + 1;
    g_Task->unk_5F = (rand() & 3) + 1;
    g_Task->unk_09 = 0;
    g_Task->timer  = 0x10;
    g_Task->header.step += 1;
}

/* blocker: retail reloads g_Task after rand() for the 0x09 update; first diff: lhu v0 against lbu v0 at 0x801F05C8. */
INCLUDE_ASM(func_801F05AC);

/* blocker: retail reloads g_Task after rand() for both the 0x2E and timer updates; first diff: lui v1 against a0 at 0x801F0664. */
INCLUDE_ASM(func_801F0638);

INCLUDE_ASM(func_801F06D8);
