#include "magic057_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC50 */
#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EECB0(void) {
    g_SpadWork->coord_x_34.raw = BATTLE_ACTIVE_WORK->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw = BATTLE_ACTIVE_WORK->coord_y_38.raw;
    g_SpadWork->word_3C.word   = BATTLE_ACTIVE_WORK->word_3C.word;
    GFX_CopyPalette(0x1A);
    g_GfxPalettePending += 1;
    g_SpadWork->step_01 += 1;
}

MATCH void func_801EED2C(void) {
    BattleResultRings table;

    table = D_801EEC10;
    SYS_DISPATCH_TASK(table.handlers, 2, g_SpadWork);
}

MATCH void func_801EED98(void) {
    PartyBattler* temp_s0;
    s32           slot;

    SND_QueueSelectionFx(0x101);
    SND_QueueSelectionFx(0x102);
    temp_s0    = g_SpadWork;
    g_SpadWork = D_801EC2E0->target.party;
    Actor_SelectScript(3U);
    g_SpadWork                         = temp_s0;
    slot                               = Battle_AllocEffect(1, 0x41) & BYTE_MASK;
    g_BattleEffects[slot].unk_01       = 1;
    g_BattleEffects[slot].unk_02       = 0;
    g_BattleEffects[slot].target.party = g_SpadWork;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EEE50(void) {
    PartyBattler* temp_s0;

    temp_s0    = g_SpadWork;
    g_SpadWork = D_801EC2E0->target.party;
    func_8014DAEC();
    g_SpadWork                        = temp_s0;
    temp_s0->word_08.byte.unk_09      = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
}

/* Scheduling residual: one spad cell read hoists above the row stores and one tail instruction is
 * missing (candidate 0xF0 vs retail 0xF4; first difference lui a1,0x1f80 at 0x801EEF28). Typed
 * g_BattleEffects form; permuter best 555/800 after 7 min. */
INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFA4(void) {
    if (g_SpadWork->word_08.byte.unk_09 == g_SpadWork->word_08.byte.timer_0A) {
        g_SpadWork->step_01 += 1;
        g_SpadWork->unk_02 = 0;
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
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

MATCH void func_801EF08C(void) {
    BattleHandlerTable3 handlers;

    handlers     = D_801EEC2C;
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
    if (g_SpadWork->flags_00 & 1) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

/* Branch residual: both arms' (rand() % 6) << 0x10 prefixes cross-jump into one shared prefix (the
 * rand call included) while retail keeps per-arm sequences with the arm constant in the j delay
 * slot (first difference: the beqz v0 target at 0x801EF150); asymmetric arm order merges harder and
 * drifts the frame. Next lever: permuter. */
INCLUDE_ASM(func_801EF134);

/* Scheduling residual: the y-store's D_801EB4E0 deref hoists above the rand()%6 division tail while
 * retail keeps it late (candidate 0x168 vs retail 0x164; first difference sra a0,v0,0x1f at
 * 0x801EF440). Clean % and the m2c decomposition sit one instruction away; the operand swap does
 * not move the deref. Next lever: permuter. */
INCLUDE_ASM(func_801EF3C4);

MATCH void func_801EF528(void) {
    PartyBattler* work;

    work                        = (PartyBattler*)D_801EB4E0;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A + 1;
    func_801E5988();
}

MATCH void func_801EF55C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC38;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}

MATCH void func_801EF5BC(void) {
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = D_801EFADC[g_SpadWork->word_08.byte.unk_09];
    SND_QueueSelectionFx(256);
    g_SpadWork->unk_10 = 0;
    g_SpadWork->unk_02++;
}

/* The local-table dispatch (Callback table[2] = {func_801EF7A0, func_801EF7E0}) is right; the body
 * stays 2-3 instructions fat, which shifts the linked table constants +8/+C. The timer compare must
 * keep (temp & 0xFF) before the beq (u8 temps add 3 instructions, s32 temps fold the mask away).
 * Next lever: permuter. */
INCLUDE_ASM(func_801EF620);

MATCH void func_801EF7A0(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->unk_10 >= -2) {
        work->unk_10--;
    } else {
        work->unk_03++;
    }
}

MATCH void func_801EF7E0(void) {
    PartyBattler* work;

    work = g_SpadWork;
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
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
    if ((g_SpadWork->flags_00 & 1) && (D_801EB4E0->word_08.byte.timer_0A == 0)) {
        func_8014D290();
    }
    g_ScriptBank = 0x800D3800;
}

MATCH void func_801EF900(void) {
    PartyBattler* work;
    s16           temp_v0;
    s32           temp_a0;
    s8            tone;

    g_SpadWork->coord_x_34.raw = D_801EB4E0->coord_x_34.raw - 1;
    g_SpadWork->coord_y_38.raw = D_801EB4E0->coord_y_38.raw - 1;
    temp_a0                    = g_SpadWork->coord_x_34.raw;
    temp_v0                    = Area_SampleHeight(temp_a0, temp_a0);
    work                       = g_SpadWork;
    work->unk_25               = 0x1D;
    work->word_3C.half.span_3E = temp_v0;
    g_SpadWork->unk_26         = 0;
    g_SpadWork->unk_48         = 1;
    g_SpadWork->unk_27         = 0xA0;
    g_SpadWork->unk_28         = 0;
    g_SpadWork->unk_24         = 4;
    tone                       = -0x80;
    g_SpadWork->unk_5D         = tone;
    g_SpadWork->unk_5E         = tone;
    g_SpadWork->unk_5F         = tone;
    g_SpadWork->unk_5C         = 0;
    g_SpadWork->unk_2A         = 0;
    g_SpadWork->unk_29         = 4;
    g_SpadWork->unk_2C.half    = 0;
    Actor_SelectScript(0U);
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EFA38(void) {
    s32 temp_a0;

    g_SpadWork->coord_x_34.raw       = D_801EB4E0->coord_x_34.raw - 1;
    g_SpadWork->coord_y_38.raw       = D_801EB4E0->coord_y_38.raw - 1;
    temp_a0                          = g_SpadWork->coord_x_34.raw;
    g_SpadWork->word_3C.half.span_3E = Area_SampleHeight(temp_a0, temp_a0);
    if (!(1 & D_801EB4E0->flags_00)) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EFABC(void) {
    func_801E5988();
}
