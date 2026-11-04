#include "magic126_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEED0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF14);

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF00C(void) {
    g_SpadWork->unk_09 += 2;
    g_SpadWork->unk_0A += 24;
    if (g_SpadWork->unk_09 == 0x10) {
        Bmagic_NextStep();
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1C8);

INCLUDE_ASM(func_801EF438);

INCLUDE_ASM(func_801EF7A4);

MATCH void func_801EFAF4(void) {
    SYS_DISPATCH_BYTE(D_801F1278, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801EFD5C();
    }
}

INCLUDE_ASM(func_801EFB74);

MATCH void func_801EFC28(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->unk_09++;
    work = g_SpadWork;
    work->unk_0A++;
    if (work->unk_0A == 16) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801EFC94(void) {
    u8 timer;

    timer              = g_SpadWork->unk_09 + 2;
    g_SpadWork->unk_09 = timer;
    if (timer == 150) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

INCLUDE_ASM(func_801EFD5C);

MATCH void func_801F01C0(void) {
    SYS_DISPATCH_BYTE(D_801F1288, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_800AF764();
        func_801F06AC();
    }
}

INCLUDE_ASM(func_801F0240);

INCLUDE_ASM(func_801F037C);

INCLUDE_ASM(func_801F0494);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801F06AC);

MATCH void func_801F091C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 19), 1, D_801F22BC);
}

MATCH void func_801F0960(void) {
    SYS_DISPATCH_BYTE(D_801F12AC, D_801F22BC->unk_02);
    if (D_801F22BC->flags_00 != 0 && D_801F22BC->unk_02 != 0) {
        func_801F11AC();
        func_801F0ED0();
    }
}

INCLUDE_ASM(func_801F09E0);

INCLUDE_ASM(func_801F0B34);

INCLUDE_ASM(func_801F0C7C);

INCLUDE_ASM(func_801F0DA4);

INCLUDE_ASM(func_801F0ED0);

INCLUDE_ASM(func_801F1110);

INCLUDE_ASM(func_801F116C);

MATCH void func_801F11AC(void) {
    PartyBattler* work;
    s16           vec[3];
    TILE_1*       primitive;

    work      = D_801F22BC;
    vec[0]    = (s16)(work->unk_10 >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (s16)(work->unk_14 >> 9) - 0x4000;
    vec[2]    = -((s16)(*(u16*)((u8*)work + 0x1A)) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    ((s16*)&D_801F22BC->unk_0C)[0] = primitive->x0;
    ((s16*)&D_801F22BC->unk_0C)[1] = primitive->y0;
}
