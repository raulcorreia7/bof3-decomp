#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EF000(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
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

MATCH void func_801EF350(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_0B & 0x80) {
        work->unk_02++;
    }
}

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

INCLUDE_ASM(func_801EF940);

INCLUDE_ASM(func_801EF990);

INCLUDE_ASM(func_801EFA24);

INCLUDE_ASM(func_801EFB04);

INCLUDE_ASM(func_801F0260);

INCLUDE_ASM(func_801F0320);

INCLUDE_ASM(func_801F038C);

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

INCLUDE_ASM(func_801F0420);

INCLUDE_ASM(func_801F04BC);

/* func_801F0758 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
