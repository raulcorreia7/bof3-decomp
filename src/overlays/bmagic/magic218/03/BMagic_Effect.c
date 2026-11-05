#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDB8};

    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEE18(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(D_801EF774, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF250();
        PopMatrix();
    }
}

MATCH void func_801EEEE4(void) {
    PartyBattler* src;
    PartyBattler* dst;

    if (--g_SpadWork->word_08.byte.unk_09 == 0) {
        src                               = BATTLE_ACTIVE_WORK;
        dst                               = g_SpadWork;
        dst->coord_x_34                   = src->coord_x_34;
        dst->coord_y_38                   = src->coord_y_38;
        dst->word_3C                      = src->word_3C;
        dst->unk_5D                       = 0x10;
        g_SpadWork->word_08.byte.unk_09   = 0x10;
        g_SpadWork->word_08.byte.timer_0A = 4;
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EEF84);

MATCH void func_801EF0F0(void) {
    u8 count;
    u8 timer;

    if (g_FrameCount & 1) {
        timer = g_SpadWork->word_08.byte.timer_0A;
        if (timer < 0x20U) {
            g_SpadWork->word_08.byte.timer_0A = timer + 1;
        }
    }
    g_SpadWork->word_08.byte.unk_09 += 1;
    count              = g_SpadWork->unk_5D - 1;
    g_SpadWork->unk_5D = count;
    if ((count << 0x18) == 0) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF250);

INCLUDE_ASM(func_801EF70C);
