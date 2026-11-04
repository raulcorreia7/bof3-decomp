#include "magic056_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC94);

INCLUDE_ASM(func_801EEF3C);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EF1B0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF1F4(void) {
    SYS_DISPATCH_BYTE(D_801F0754, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF4C0();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

INCLUDE_ASM(func_801EF2DC);

INCLUDE_ASM(func_801EF37C);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4C0);

MATCH void func_801EFA50(void) {
    SYS_DISPATCH_BYTE(D_801F0760, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void Effect_CopyBattlerCoords_801EFAD8(void) {
    PartyBattler* src;

    BMAGIC_COPY_BATTLER_COORDS();
}

MATCH void func_801EFB38(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_0A += 2;
    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 12) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801EFBA4(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 30) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

INCLUDE_ASM(func_801EFC74);

INCLUDE_ASM(func_801EFF28);

MATCH void func_801EFFE8(void) {
    g_SpadWork->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_SpadWork->unk_02++;
}

INCLUDE_ASM(func_801F0024);

INCLUDE_ASM(func_801F00C8);

INCLUDE_ASM(func_801F0178);

INCLUDE_ASM(func_801F023C);

INCLUDE_ASM(func_801F042C);

INCLUDE_ASM(func_801F04EC);

INCLUDE_ASM(func_801F0658);

MATCH void func_801F0724(void) {
    func_801E5988();
}
