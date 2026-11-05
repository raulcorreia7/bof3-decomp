#include "magic123_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EEDAC);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0C4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF108(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 2), 2, g_Task);
}

MATCH void func_801EF14C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_2E.half = D_801EB4E0->unk_2E.half;
        g_Task->unk_30.half = D_801EB4E0->unk_30.half;
        if (rand() & 1) {
            g_Task->unk_14 = D_801EB4E0->unk_14 + (rand() & BYTE_MASK);
        } else {
            g_Task->unk_14 = D_801EB4E0->unk_14 - (rand() & BYTE_MASK);
        }
        g_Task->unk_03 = rand() & 7;
        g_Task->unk_0C = (rand() & 7) + 8;
        g_Task->unk_0B = rand();
        g_Task->unk_09 = (rand() & 0xF) + 8;
        g_Task->timer  = 2;
        g_Task->step += 1;
    }
}

INCLUDE_ASM(func_801EF28C);

MATCH void func_801EF4AC(void) {
    u8 timer;

    g_Task->unk_0B += 1;
    g_Task->unk_09 += 1;
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & 0xFF)) {
        BATTLE_ACTIVE_WORK->unk_0B -= 1;
        Actor_Clear();
        return;
    }
    func_801EF9E0();
}

MATCH void func_801EF550(void) {
    BATTLE_ACTIVE_WORK->unk_0B--;
    Actor_Clear();
}

INCLUDE_ASM(func_801EF584);

INCLUDE_ASM(func_801EF750);

INCLUDE_ASM(func_801EF9E0);

/* func_801EFCA0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFD04 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
