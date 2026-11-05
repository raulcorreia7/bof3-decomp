#include "magic001_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EECC4);

MATCH void func_801EEF34(void) {
    BMagic_ClearWorkFlagsAndStep();
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEFD8(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF01C);

MATCH void func_801EF0E8(void) {
    func_801E257C((u32)g_BattleActingBattler, 0xAU);
    g_SpadWork->unk_27                = D_801EB4E0->unk_27;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EF164(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 0);
        func_801E257C((u32)g_BattleActingBattler, 0xBU);
        g_SpadWork->unk_14 = 0x100;
        g_SpadWork->unk_20 = -8;
        g_SpadWork->unk_02 += 1;
    }
}

/* needs: type g_BattleSelectedActor. Retail rereads it before the second coordinate copy, as a member of an aggregate
 * would (the BattleAction block at 0x80146380 +0x0C); a plain global keeps it in a register. Exact in a scratch build with
 * the pointer declared as an array element; as a plain global the first differing instruction is the bnez target at +0x2C. */
INCLUDE_ASM(func_801EF1CC);

MATCH void func_801EF280(void) {
    PartyBattler* work;
    u8            timer;

    work                      = g_SpadWork;
    timer                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = timer;
    work->unk_14 += work->unk_20;
    work->word_3C.half.span_3E += work->unk_14;
    if (timer == 0) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_BattleActingBattler, 0xC);
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->word_08.byte.unk_09 = 3;
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF324(void) {
    if (func_8014DAEC() != 0u) {
        func_801E257C(g_BattleActingBattler, 0xA);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF37C(void) {
    PartyBattler* work;

    func_8014DAEC();
    func_8014DAEC();
    if (func_8014DAEC() & BYTE_MASK) {
        func_800AFC98(2, 0);
        func_801E257C(g_BattleActingBattler, 0xB);
        work                        = g_SpadWork;
        work->unk_14                = 0x140;
        work->word_08.byte.timer_0A = 9;
        work->unk_20                = -0x40;
        g_SpadWork->unk_02++;
    }
}

INCLUDE_ASM(func_801EF408);

MATCH void func_801EF468(void) {
    u8 timer;

    func_8014DAEC();
    func_8014DAEC();
    if (func_8014DAEC() & BYTE_MASK) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_BattleActingBattler, 0xC);
        timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = timer;
        if (timer != 0) {
            g_SpadWork->unk_02 -= 3;
        } else {
            g_SpadWork->unk_02++;
        }
    }
}

MATCH void func_801EF518(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C = 1;
        g_SpadWork->unk_5D = 0;
        g_SpadWork->unk_5E = 0;
        g_SpadWork->unk_5F = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF5CC);

#include "overlays/bmagic/Effect_RampTintAndFinish.h"

MATCH void func_801EF688(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

MATCH void func_801EF72C(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EF78C);

MATCH void func_801EFA14(void) {
    BMagic_ClearWorkFlagsAndStep();
}

MATCH void Effect_StartPlaying_801EFA84(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFAB8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_SpadWork);
}

INCLUDE_ASM(func_801EFAFC);

MATCH void func_801EFBEC(void) {
    g_SpadWork->unk_27                = D_801EB4E0->unk_27;
    g_SpadWork->unk_14                = 0x100;
    g_SpadWork->unk_20                = -0x10;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0x10;
    g_SpadWork->unk_02 += 1;
}

/* needs: type g_BattleSelectedActor. Retail rereads it before the second coordinate copy, as a member of an aggregate
 * would (the BattleAction block at 0x80146380 +0x0C); a plain global keeps it in a register. Exact in a scratch build with
 * the pointer declared as an array element; as a plain global the first differing instruction is the bnez target at +0x4C. */
INCLUDE_ASM(func_801EFC54);

MATCH void func_801EFD28(void) {
    s32 temp_v1;
    u8  temp_a1;
    u8  temp_v0;

    temp_a1                          = g_SpadWork->word_08.byte.timer_0A;
    temp_v1                          = g_SpadWork->unk_14 + g_SpadWork->unk_20;
    g_SpadWork->unk_14               = temp_v1;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E + temp_v1;
    if (temp_a1 < 8U) {
        g_SpadWork->word_08.byte.timer_0A = temp_a1 + 1;
    }
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800AFC98(2, 0);
        SND_QueueSelectionFx(0x203);
        g_SpadWork->unk_14 = 0x40;
        g_SpadWork->unk_20 = -8;
        g_SpadWork->unk_0C = ratan2(D_801EB4E0->coord_x_34.raw - g_SpadWork->coord_x_34.raw,
                                    D_801EB4E0->coord_y_38.raw - g_SpadWork->coord_y_38.raw);
        /* FAKE: Without the barrier, the scheduler sinks the angle store into the call's delay slot. */
        MATCH_FAKE_BARRIER();
        func_800A9820(g_BattleTargetSelector);
        g_SpadWork->word_08.byte.unk_09 = 0x10;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EFE38(void) {
    s32 value;
    u8  value2;
    u8  value3;

    g_SpadWork->coord_x_34.raw += (s32)(rsin(g_SpadWork->unk_0C) << 0xD) >> 0xC;
    g_SpadWork->coord_y_38.raw += (s32)(rcos(g_SpadWork->unk_0C) << 0xD) >> 0xC;
    value                            = g_SpadWork->unk_14 + g_SpadWork->unk_20;
    g_SpadWork->unk_14               = value;
    g_SpadWork->word_3C.half.span_3E = (u16)g_SpadWork->word_3C.half.span_3E + value;
    if ((u8)g_SpadWork->word_08.byte.unk_09 < 8U) {
        value3 = g_SpadWork->word_08.byte.timer_0A;
        if (value3 < 0x10U) {
            g_SpadWork->word_08.byte.timer_0A = value3 + 1;
        }
    }
    value2                          = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value2;
    if (!(value2 & 0xFF)) {
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801EFFCC(void) {
    PartyBattler* work;
    PartyBattler* source;
    s8            temp_v0;
    u8            temp_v0_2;

    temp_v0 = (s8)g_SpadWork->unk_5D;
    if (temp_v0 != -0x80) {
        g_SpadWork->unk_5D = temp_v0 - 0x10;
        g_SpadWork->unk_5E -= 0x10;
        g_SpadWork->unk_5F -= 0x10;
    }
    temp_v0_2 = g_SpadWork->word_08.byte.timer_0A;
    if (temp_v0_2 != 0) {
        g_SpadWork->word_08.byte.timer_0A = temp_v0_2 - 2;
    }
    if ((s8)g_SpadWork->unk_5D == -0x80) {
        work                 = g_SpadWork;
        source               = BATTLE_ACTIVE_WORK;
        work->coord_x_34.raw = source->coord_x_34.raw;
        work->coord_y_38.raw = source->coord_y_38.raw;
        work->word_3C.word   = source->word_3C.word;
        work->unk_02 += 1;
    }
}

MATCH void func_801F00A8(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

INCLUDE_ASM(func_801F014C);

INCLUDE_ASM(func_801F0238);
