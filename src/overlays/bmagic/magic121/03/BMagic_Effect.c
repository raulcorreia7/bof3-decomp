#include "magic121_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEE08};
    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEE68(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEEAC);

INCLUDE_ASM(func_801EF03C);

MATCH void func_801EF218(void) {
    u8 timer;

    timer         = g_Task->timer + 8;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer          = g_Task->unk_0B + 1;
    g_Task->unk_0B = timer;
    if (timer == 8) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->step = g_Task->step + 1;
    }
}

#include "../../Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF324(void) {
    PartyBattler* work;

    work = g_Task;
    if (++work->unk_0C == 0x2E) {
        work->step++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer          = g_Task->unk_04 - 2;
    g_Task->unk_04 = timer;
    if (timer == 0) {
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF3A8(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = g_Task->unk_0B;
    if (temp_v0 != 0) {
        g_Task->unk_0B = temp_v0 - 1;
    }
    temp_v0_2      = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->unk_0B = 0xFF;
        func_801E5988();
    }
}

/* blocker: sp20 and sp18 stores scheduling; first diff: +0x80. */
INCLUDE_ASM(func_801EF414);

INCLUDE_ASM(func_801F0198);

INCLUDE_ASM(func_801F06E8);
