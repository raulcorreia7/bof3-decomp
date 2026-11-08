#include "magic017_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC98);

#include "overlays/bmagic/Effect_ReleaseActiveBattlerOnTickerZero.h"

MATCH void func_801EEFD8(void) {
    u16* flags;

    func_800AFC54();
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
    func_801E5988();
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

/* hint: the eight-entry copy into a local EffectStepFuncs8 is unrolled by the candidate; first differing instruction is the addiu t0,a2,32 at +0x14 (retail runs the copy as a 16-byte loop with bne). */
INCLUDE_ASM(func_801EF058);

/* blocker: work pointer reload; first diff: +0xB0 lui v1,0x1f80 (retail reloads g_Task for the unk_27 store and again before the call) against a0 held across both (candidate). */
INCLUDE_ASM(func_801EF11C);

INCLUDE_ASM(func_801EF248);

/* blocker: y store; first diff: +0x34 sw v0,0x10(v1) shared after the branches (retail) against the constant hoisted to a2 across the call (candidate). */
INCLUDE_ASM(func_801EF300);

MATCH void func_801EF460(void) {
    PartyBattler* task;
    u8            timer;

    task = g_Task;
    task->pos.x.fixed += task->unk_0C;
    task->unk_5D += 4;
    task->pos.y.fixed += task->unk_10;
    g_Task->unk_5E += 4;
    g_Task->unk_5F += 4;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        if (g_Task->param.unk_0B == 0) {
            g_Task->header.flags &= 0xDF;
            g_Task->unk_5C = 0;
            g_Task->unk_2B = 0;
            g_Task->unk_5D = 0;
            g_Task->unk_5E = 0;
            g_Task->unk_5F = 0;
            if (g_BattleActiveBattler >= 3) {
                func_801E257C(g_BattleActiveBattler, 2);
            }
            g_Task->unk_09 = func_800AFF98();
            g_Task->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF5FC(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->param.unk_0B == 1) {
        func_8014DAEC();
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & 0xFF)) {
            func_800A9820(g_BattleTargetSelector);
            func_800AFC98(2, 4);
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801EF694(void) {
    if (func_8014DAEC() != 0u) {
        g_Task->unk_09      = 8;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF6EC(void) {
    s8 tone;
    u8 temp_v0;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        if (g_BattleActiveBattler >= 3U) {
            func_801E257C(g_BattleActiveBattler, 0);
        }
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_2B = 1;
        tone           = -0x40;
        g_Task->unk_5D = tone;
        g_Task->unk_5E = tone;
        g_Task->unk_5F = tone;
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF7E0(void) {
    u8 timer;

    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_09      = 8;
        g_Task->header.step++;
    }
}

MATCH void func_801EF8B4(void) {
    u8 count;

    g_Task->unk_5D += 8;
    g_Task->unk_5E += 8;
    g_Task->unk_5F += 8;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & 0xFF)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF970(void) {
    func_801E5988();
}
