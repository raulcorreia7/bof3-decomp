#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED28);

INCLUDE_ASM(func_801EEE50);

MATCH void func_801EEF54(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionFx(0x101);
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF024(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF068);

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF3CC);

MATCH void func_801EF530(void) {
    PartyBattler* work = g_SpadWork;

    work->unk_25         = 0x1D;
    work->coord_x_34.raw = work->unk_0C;
    work->coord_y_38.raw = work->unk_10;
    work->word_3C.word   = work->unk_14;
    g_SpadWork->unk_26   = 0;
    g_SpadWork->unk_27   = 0x1A;
    g_SpadWork->unk_2B   = 1;
    Actor_SelectScript(1);
    g_SpadWork->word_08.byte.unk_09   = 0xE;
    g_SpadWork->word_08.byte.timer_0A = 0xC;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF5DC(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    func_8014DAEC();
    temp_v0 = g_SpadWork->word_08.byte.timer_0A;
    if (temp_v0 != 0) {
        g_SpadWork->word_08.byte.timer_0A = temp_v0 - 1;
    }
    temp_v0_2                       = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF71C);

/* func_801EF934 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF998 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
