#include "magic154_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

INCLUDE_ASM(func_801EEC90);

INCLUDE_ASM(func_801EEE94);

MATCH void func_801EEFE0(void) {
    if (g_SpadWork->word_08.byte.unk_09 == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        func_800A9610(g_BattleTargetSelector, 0x10U);
        g_SpadWork->step_01 += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF0C0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF104);

INCLUDE_ASM(func_801EF1EC);

MATCH void func_801EF380(void) {
    PartyBattler* work;
    u8            count;

    work = g_SpadWork;
    work->unk_40 += 0x4000;
    count                     = work->word_08.byte.unk_09 + 1;
    work->word_08.byte.unk_09 = count;
    work->unk_44              = work->unk_44 + 0x8000;
    if (count == 4) {
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EF3E4);

MATCH void func_801EF454(void) {
    g_SpadWork->unk_44 -= 0x1000;
    if ((s8)g_SpadWork->unk_5F == -0x80) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4B4);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

INCLUDE_ASM(func_801EF58C);

MATCH void func_801EF648(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_09--;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF6AC(void) {
    func_801E5988();
}
