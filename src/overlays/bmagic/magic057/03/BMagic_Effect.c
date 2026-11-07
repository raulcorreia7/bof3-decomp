#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EECB0(void) {
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed;
    g_Task->pos.z.fixed = BATTLE_ACTIVE_WORK->pos.z.fixed;
    GFX_CopyPalette(0x1A);
    g_GfxPalettePending += 1;
    g_Task->header.mode += 1;
}

MATCH void func_801EED2C(void) {
    BattleHandlerTable4 table;

    table = D_801EEC10;
    SYS_DISPATCH_TASK(table.handlers, 2, g_Task);
}

MATCH void func_801EED98(void) {
    PartyBattler* temp_s0;
    s32           slot;

    SND_QueueSelectionFx(0x101);
    SND_QueueSelectionFx(0x102);
    temp_s0 = g_Task;
    g_Task  = D_801EC2E0->target.party;
    Actor_SelectScript(3U);
    g_Task                             = temp_s0;
    slot                               = Battle_AllocEffect(1, 0x41) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].target.party = g_Task;
    g_Task->header.step += 1;
}

MATCH void func_801EEE50(void) {
    PartyBattler* temp_s0;

    temp_s0 = g_Task;
    g_Task  = D_801EC2E0->target.party;
    func_8014DAEC();
    g_Task          = temp_s0;
    temp_s0->unk_09 = 0;
    g_Task->timer   = 0;
}

/* blocker: spad cell read hoisted; first diff: lui a1,0x1f80 at 0x801EEF28. */
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
    func_800A9820(*(battle_flags = &g_BattleTargetSelector));
    func_801E5988();
}

MATCH void func_801EF02C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_Task);
}

MATCH void func_801EF08C(void) {
    BattleHandlerTable3 handlers;

    handlers     = D_801EEC2C;
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
    if (g_Task->header.flags & 1) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

/* blocker: cross-jumped (rand() % 6) << 0x10 prefixes; first diff: beqz v0 target at 0x801EF150. */
INCLUDE_ASM(func_801EF134);

/* blocker: y-store deref hoisted; first diff: sra a0,v0,0x1f at 0x801EF440. */
INCLUDE_ASM(func_801EF3C4);

MATCH void func_801EF528(void) {
    PartyBattler* work;

    work        = (PartyBattler*)g_BattleEffectBattler;
    work->timer = work->timer + 1;
    func_801E5988();
}

MATCH void func_801EF55C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC38;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
}

MATCH void func_801EF5BC(void) {
    g_Task->unk_09 = 0;
    g_Task->timer  = D_801EFADC[g_Task->unk_09];
    SND_QueueSelectionFx(256);
    g_Task->unk_10 = 0;
    g_Task->header.step++;
}

/* blocker: body 2-3 instructions fat; first diff: linked table constants +8 and +C. */
INCLUDE_ASM(func_801EF620);

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

MATCH void func_801EF7E0(void) {
    PartyBattler* work;

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
    BattleHandlerTable3 handlers;

    handlers     = D_801EEC44;
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_Task);
    if ((g_Task->header.flags & 1) && (g_BattleEffectBattler->timer == 0)) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

MATCH void func_801EF900(void) {
    PartyBattler* work;
    s16           temp_v0;
    s32           temp_a0;
    s8            tone;

    g_Task->pos.x.fixed    = g_BattleEffectBattler->pos.x.fixed - 1;
    g_Task->pos.y.fixed    = g_BattleEffectBattler->pos.y.fixed - 1;
    temp_a0                = g_Task->pos.x.fixed;
    temp_v0                = Area_SampleHeight(temp_a0, temp_a0);
    work                   = g_Task;
    work->unk_25           = 0x1D;
    COORD_INT(work->pos.z) = temp_v0;
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
    s32 temp_a0;

    g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed - 1;
    g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed - 1;
    temp_a0                  = g_Task->pos.x.fixed;
    COORD_INT(g_Task->pos.z) = Area_SampleHeight(temp_a0, temp_a0);
    if (!(1 & g_BattleEffectBattler->header.flags)) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFABC(void) {
    func_801E5988();
}
