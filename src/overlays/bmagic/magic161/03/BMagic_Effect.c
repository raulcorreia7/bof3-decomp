#include "magic161_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC84);

MATCH void func_801EEE9C(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(0x18, 0);
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH s32 func_801EEF3C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEF80(void) {
    Magic161Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF06C(void) {
    u8 count;

    Actor_StepAnimOnce();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        func_800AFC98(2, 4);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0E8(void) {
    u8 count;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) == 0x10) {
        SND_QueueSelectionFx(0x100);
        g_Task->header.step += 1;
    } else {
        g_Task->unk_09 = count + 4;
    }
    func_801EF1DC();
    Actor_StepAnimOnce();
}

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EF1BC(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF1DC);
