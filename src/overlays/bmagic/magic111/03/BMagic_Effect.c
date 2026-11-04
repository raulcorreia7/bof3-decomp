#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC7C);

INCLUDE_ASM(func_801EEF44);

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFF8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF03C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0C0(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_29 = 2;
    work         = g_SpadWork;
    work->unk_02 = (u8)(work->unk_02 + 1);
}

MATCH void func_801EF0F0(void) {
    u8            step;
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    step = work->unk_0B;
    if (step < 2) {
        work->unk_0B       = step - 1;
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF138(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF1D4);

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801EF330);

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801EF970();
    }
}

INCLUDE_ASM(func_801EF870);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801EF914(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->unk_09 -= 2;
    if (work->unk_09 == 0) {
        work = (PartyBattler*)D_801EB4E0;
        work->unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF970);
