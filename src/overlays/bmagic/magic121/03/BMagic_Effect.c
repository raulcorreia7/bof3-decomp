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

/* func_801EEE68 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

INCLUDE_ASM(BMagic_UpdateDragonBreath);

INCLUDE_ASM(func_801EF03C);

MATCH void func_801EF218(void) {
    u8 timer;

    timer         = g_Task->timer + 8;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer                = g_Task->param.unk_0B + 1;
    g_Task->param.unk_0B = timer;
    if (timer == 8) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF324(void) {
    PartyMember* work;

    work = g_Task;
    if (++work->unk_0C == 0x2E) {
        work->header.step++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer          = g_Task->unk_04 - 2;
    g_Task->unk_04 = timer;
    if (timer == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF3A8(void) {
    u8 ticks;
    u8 count;

    ticks = g_Task->param.unk_0B;
    if (ticks != 0) {
        g_Task->param.unk_0B = ticks - 1;
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(BMagic_DrawDragonBreath);

INCLUDE_ASM(func_801F0198);

INCLUDE_ASM(func_801F06E8);
