#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF000(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EF044(void) {
    SYS_DISPATCH_BYTE(D_801F07C0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF580();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF0CC);

INCLUDE_ASM(func_801EF1F0);

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

INCLUDE_ASM(func_801EF388);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF580);

MATCH void func_801EF7FC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 5), 1, g_SpadWork);
}

MATCH void func_801EF840(void) {
    SYS_DISPATCH_BYTE(D_801F07D8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EFB04();
    }
}

INCLUDE_ASM(func_801EF8C0);

MATCH void func_801EF940(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

MATCH void func_801EF990(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    g_SpadWork->word_08.byte.timer_0A += 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0x19) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B |= 0x80;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EFA24(void) {
    g_SpadWork->word_08.byte.unk_09 -= 2;
    if (g_FrameCount & 1) {
        g_SpadWork->word_08.byte.timer_0A += 1;
    }
    if (g_SpadWork->word_08.byte.unk_09 == 1) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}

INCLUDE_ASM(func_801EFB04);

INCLUDE_ASM(func_801F0260);

INCLUDE_ASM(func_801F0320);

MATCH void func_801F038C(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

MATCH void func_801F0420(void) {
    u8 counter;

    counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if (!(counter & 0xFF)) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->flags_00 = 0;
        g_SpadWork->step_01  = 0;
        g_SpadWork->unk_02   = 0;
        g_SpadWork->unk_03   = 0;
        g_SpadWork->unk_04   = 0;
    }
}

INCLUDE_ASM(func_801F04BC);

/* func_801F0758 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
