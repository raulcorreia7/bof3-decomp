#include "magic125_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEC0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF04);

MATCH void func_801EEFF8(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->coord_x_34.raw        = D_801EB4E0->coord_x_34.raw;
        g_SpadWork->coord_y_38.raw        = D_801EB4E0->coord_y_38.raw;
        g_SpadWork->word_3C.word          = D_801EB4E0->word_3C.word + 0x04000000;
        g_SpadWork->unk_5D                = (rand() & 3) + 4;
        g_SpadWork->unk_5E                = (rand() & 3) + 4;
        g_SpadWork->unk_5F                = (rand() & 3) + 4;
        g_SpadWork->unk_14                = 0x100;
        g_SpadWork->word_08.byte.unk_09   = 0x10;
        g_SpadWork->word_08.byte.timer_0A = 8;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF0F8);

INCLUDE_ASM(func_801EF148);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF258);

INCLUDE_ASM(func_801EF508);

MATCH void func_801EF808(void) {
    SYS_DISPATCH_BYTE(D_801F05EC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF508();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF890);

INCLUDE_ASM(func_801EF960);

MATCH void func_801EFAB0(void) {
    s32 temp_v1;
    u8  counter;

    temp_v1 = g_SpadWork->unk_14;
    if (temp_v1 >= 9) {
        g_SpadWork->unk_14 = temp_v1 - 1;
    }
    if (g_FrameCount & 1) {
        counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = counter;
        if (!(counter & 0xFF)) {
            BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
            func_801E5988();
        }
    }
}

MATCH void func_801EFB48(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 8), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFB8C);

INCLUDE_ASM(func_801EFCE4);

INCLUDE_ASM(func_801EFE8C);

INCLUDE_ASM(func_801EFFC8);

INCLUDE_ASM(func_801F020C);

/* func_801F0524 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0588 */
MATCH void Actor_Clear(void) {
    Bmagic_ResetLocalWork();
}
