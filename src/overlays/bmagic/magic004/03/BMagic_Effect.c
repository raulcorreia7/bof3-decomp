#include "magic004_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

INCLUDE_ASM(func_801EEF8C);

MATCH void func_801EF158(void) {
    u16 cue;

    if (g_Task->param.unk_0B == 0) {
        cue = D_801EFE40[g_Task->unk_04];
        if (cue != 0) {
            SND_QueueSelectionFx(cue);
        }
        func_800A9820(g_Battle.target_selector);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801EF1F0);

INCLUDE_ASM(func_801EF3E0);

INCLUDE_ASM(func_801EF490);

/* func_801EF6E0 */
#include "overlays/bmagic/Effect_DrawScreenFade.h"

MATCH void func_801EF8CC(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF910(void) {
    Magic004Steps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

/* blocker: branch over the g_Battle.action_id < 0x85 test; first diff: 0x801EFA18. */
/* blocker: the zero branch compares the timer with a branch retail places after the table lookup; first diff: bnez v0 at 0x801EFA18. */
INCLUDE_ASM(func_801EF9E8);

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EFAD4(void) {
    func_801E5988();
}

/* func_801EFAF4 */
#include "overlays/bmagic/BMagic_RunStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

INCLUDE_ASM(func_801EFBEC);

MATCH void func_801EFD84(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        count -= 1;
        g_Task->unk_09 = count;
        if (!(count & BYTE_MASK)) {
            SND_QueueSelectionFx(0x101);
        }
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
        return;
    }
    func_8014D290();
}
