#include "magic172_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDD8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE38(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEE7C);

/* blocker: copied x load schedule; first diff: lw a0 at +0x28. */
INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF210);

MATCH void func_801EF3A4(void) {
    u8 counter;
    u8 timer;

    g_Task->unk_0B += 2;
    timer = g_Task->timer;
    if (timer < 0x10U) {
        g_Task->timer = timer + 2;
    }
    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF430(void) {
    u8 temp_v0;

    g_Task->unk_0B += 4;
    temp_v0       = g_Task->timer - 2;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        SND_QueueSelectionFx(0x102);
        g_Task->unk_09 = 0x10;
        g_Task->step += 1;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"
extern Callback D_801F0B90[];
void            func_801F0908(void);

MATCH void func_801EF518(void) {
    D_801F0B90[g_Task->step]();
    if (g_Task->flags & g_Task->step) {
        func_800AF764();
        func_801F0908();
    }
}

/* blocker: early constant load; first diff: 0x801EF5B8. */
INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF650);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801EF7CC);

INCLUDE_ASM(func_801EFA2C);

INCLUDE_ASM(func_801EFD04);

INCLUDE_ASM(func_801EFFE8);

INCLUDE_ASM(func_801F02C8);

INCLUDE_ASM(func_801F05E8);

INCLUDE_ASM(func_801F0908);
