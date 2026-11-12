#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EECB0(void) {
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    GFX_CopyPalette(0x1A);
    g_GfxPalettePending += 1;
    g_Task->header.mode += 1;
}

MATCH void func_801EED2C(void) {
    Magic057Steps table;

    table = D_801EEC10;
    SYS_DISPATCH_TASK(table.steps, 2, g_Task);
}

MATCH void func_801EED98(void) {
    PartyMember* work;
    s32          slot;

    SND_QueueSelectionFx(0x101);
    SND_QueueSelectionFx(0x102);
    work   = g_Task;
    g_Task = D_801EC2E0->target.party;
    Actor_SelectScript(3U);
    g_Task                             = work;
    slot                               = Battle_AllocEffect(1, 0x41) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].target.party = g_Task;
    g_Task->header.step += 1;
}

MATCH void func_801EEE50(void) {
    PartyMember* work;

    work   = g_Task;
    g_Task = D_801EC2E0->target.party;
    Actor_StepAnimOnce();
    g_Task        = work;
    work->unk_09  = 0;
    g_Task->timer = 0;
}

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFA4(void) {
    if (g_Task->unk_09 == g_Task->timer) {
        g_Task->header.mode += 1;
        g_Task->header.step = 0;
    }
}

MATCH void func_801EEFEC(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 4;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    func_801E5988();
}

MATCH void func_801EF02C(void) {
    Magic057SecondSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EF08C(void) {
    Magic057SecondSteps handlers;

    handlers      = D_801EEC2C;
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (g_Task->header.flags & 1) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF134);

INCLUDE_ASM(func_801EF3C4);

MATCH void func_801EF528(void) {
    PartyMember* work;

    work        = (PartyMember*)g_BattleEffectBattler;
    work->timer = work->timer + 1;
    func_801E5988();
}

MATCH void func_801EF55C(void) {
    Magic057SecondSteps handlers;

    handlers = D_801EEC38;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF5BC(void) {
    g_Task->unk_09 = 0;
    g_Task->timer  = D_801EFADC[g_Task->unk_09];
    SND_QueueSelectionFx(256);
    g_Task->unk_10 = 0;
    g_Task->header.step++;
}

INCLUDE_ASM(func_801EF620);

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

MATCH void func_801EF7E0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->unk_10 < 0) {
        work->unk_10++;
    } else {
        work->unk_03--;
    }
}

MATCH void func_801EF81C(void) {
    func_801E5988();
}

MATCH void func_801EF83C(void) {
    Magic057SecondSteps handlers;

    handlers      = D_801EEC44;
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if ((g_Task->header.flags & 1) && (g_BattleEffectBattler->timer == 0)) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF900(void) {
    PartyMember* work;
    s16          height;
    s32          x;
    s8           tone;

    g_Task->pos.x.fixed    = g_BattleEffectBattler->pos.x.fixed - 1;
    g_Task->pos.y.fixed    = g_BattleEffectBattler->pos.y.fixed - 1;
    x                      = g_Task->pos.x.fixed;
    height                 = Area_SampleHeight(x, x);
    work                   = g_Task;
    work->unk_25           = 0x1D;
    COORD_INT(work->pos.z) = height;
    g_Task->unk_26         = 0;
    g_Task->unk_48         = 1;
    g_Task->unk_27         = 0xA0;
    g_Task->unk_28         = 0;
    g_Task->unk_24         = 4;
    tone                   = -0x80;
    g_Task->unk_5D         = tone;
    g_Task->unk_5E         = tone;
    g_Task->unk_5F         = tone;
    g_Task->unk_5C         = 0;
    g_Task->unk_2A         = 0;
    g_Task->unk_29         = 4;
    g_Task->unk_2C.half    = 0;
    Actor_SelectScript(0U);
    g_Task->header.step += 1;
}

MATCH void func_801EFA38(void) {
    s32 x;

    g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed - 1;
    g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed - 1;
    x                        = g_Task->pos.x.fixed;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(x, x);
    if (!(1 & g_BattleEffectBattler->header.flags)) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFABC(void) {
    func_801E5988();
}
