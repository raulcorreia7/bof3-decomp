#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic219Steps handlers = D_801EEC04;
    PartyBattler* saved_task;
    PartyBattler* saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EFA14[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyBattler*)&D_801EFA14[i];
            g_BattleEffectBattler = D_801EFA14[i].target.party;
            func_801EF024();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED28);

INCLUDE_ASM(func_801EEE50);

MATCH void func_801EEF54(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionFx(0x101);
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EF024(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EF068(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801EFA04, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF71C();
        PopMatrix();
    }
    g_ScriptBank = AREA_SCRIPT_BANK;
}

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF3CC);

MATCH void func_801EF530(void) {
    PartyBattler* work = g_Task;

    work->unk_25      = 0x1D;
    work->pos.x.fixed = work->unk_0C;
    work->pos.y.fixed = work->unk_10;
    work->pos.z.fixed = work->unk_14;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0x1A;
    g_Task->unk_2B    = 1;
    Actor_SelectScript(1);
    g_Task->unk_09 = 0xE;
    g_Task->timer  = 0xC;
    g_Task->header.step += 1;
}

MATCH void func_801EF5DC(void) {
    u8 timer_next;
    u8 count;

    func_8014DAEC();
    timer_next = g_Task->timer;
    if (timer_next != 0) {
        g_Task->timer = timer_next - 1;
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF71C);

/* func_801EF934 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF998 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
