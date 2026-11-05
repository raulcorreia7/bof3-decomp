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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EF01C);

MATCH void func_801EF0E8(void) {
    func_801E257C((u32)g_BattleActiveBattler, 0xAU);
    g_Task->unk_27 = D_801EB4E0->unk_27;
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->step += 1;
}

MATCH void func_801EF164(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800AFC98(2, 0);
        func_801E257C((u32)g_BattleActiveBattler, 0xBU);
        g_Task->unk_14 = 0x100;
        g_Task->unk_20 = -8;
        g_Task->step += 1;
    }
}

/* needs: type g_BattleSelectedActor. Retail rereads it before the second coordinate copy, as a member of an aggregate
 * would (the BattleAction block at 0x80146380 +0x0C); a plain global keeps it in a register. Exact in a scratch build with
 * the pointer declared as an array element; as a plain global the first differing instruction is the bnez target at +0x2C. */
INCLUDE_ASM(func_801EF1CC);

MATCH void func_801EF280(void) {
    PartyBattler* work;
    u8            timer;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_14 += work->unk_20;
    COORD_INT(work->pos.z) += work->unk_14;
    if (timer == 0) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_BattleActiveBattler, 0xC);
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->unk_09 = 3;
        g_Task->step++;
    }
}

MATCH void func_801EF324(void) {
    if (func_8014DAEC() != 0u) {
        func_801E257C(g_BattleActiveBattler, 0xA);
        g_Task->step = g_Task->step + 1;
    }
}

MATCH void func_801EF37C(void) {
    PartyBattler* work;

    func_8014DAEC();
    func_8014DAEC();
    if (func_8014DAEC() & BYTE_MASK) {
        func_800AFC98(2, 0);
        func_801E257C(g_BattleActiveBattler, 0xB);
        work         = g_Task;
        work->unk_14 = 0x140;
        work->timer  = 9;
        work->unk_20 = -0x40;
        g_Task->step++;
    }
}

MATCH void func_801EF408(void) {
    PartyBattler* work  = g_Task;
    u8            timer = work->timer - 1;
    s32           value = work->unk_14 + work->unk_20;
    work->timer         = timer;
    work->unk_14        = value;
    COORD_INT(work->pos.z) += value;
    if (timer == 0) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF468(void) {
    u8 timer;

    func_8014DAEC();
    func_8014DAEC();
    if (func_8014DAEC() & BYTE_MASK) {
        SND_QueueSelectionFx(0x203);
        func_801E257C(g_BattleActiveBattler, 0xC);
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (timer != 0) {
            g_Task->step -= 3;
        } else {
            g_Task->step++;
        }
    }
}

MATCH void func_801EF518(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800A9820(g_BattleTargetSelector);
        g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0;
        g_Task->unk_5E = 0;
        g_Task->unk_5F = 0;
        g_Task->step += 1;
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
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_Task);
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
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 1), 1, g_Task);
}

INCLUDE_ASM(func_801EFAFC);

MATCH void func_801EFBEC(void) {
    g_Task->unk_27 = D_801EB4E0->unk_27;
    g_Task->unk_14 = 0x100;
    g_Task->unk_20 = -0x10;
    g_Task->unk_09 = 0;
    g_Task->timer  = 0x10;
    g_Task->step += 1;
}

/* needs: type g_BattleSelectedActor. Retail rereads it before the second coordinate copy, as a member of an aggregate
 * would (the BattleAction block at 0x80146380 +0x0C); a plain global keeps it in a register. Exact in a scratch build with
 * the pointer declared as an array element; as a plain global the first differing instruction is the bnez target at +0x4C. */
INCLUDE_ASM(func_801EFC54);

MATCH void func_801EFD28(void) {
    s32 temp_v1;
    u8  temp_a1;
    u8  temp_v0;

    temp_a1                    = g_Task->timer;
    temp_v1                    = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14             = temp_v1;
    COORD_INT(g_Task->pos.z) = (u16)COORD_INT(g_Task->pos.z) + temp_v1;
    if (temp_a1 < 8U) {
        g_Task->timer = temp_a1 + 1;
    }
    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800AFC98(2, 0);
        SND_QueueSelectionFx(0x203);
        g_Task->unk_14 = 0x40;
        g_Task->unk_20 = -8;
        g_Task->unk_0C =
            ratan2(D_801EB4E0->pos.x.fixed - g_Task->pos.x.fixed, D_801EB4E0->pos.y.fixed - g_Task->pos.y.fixed);
        /* FAKE: Without the barrier, the scheduler sinks the angle store into the call's delay slot. */
        MATCH_FAKE_BARRIER();
        func_800A9820(g_BattleTargetSelector);
        g_Task->unk_09 = 0x10;
        g_Task->step += 1;
    }
}

MATCH void func_801EFE38(void) {
    s32 value;
    u8  value2;
    u8  value3;

    g_Task->pos.x.fixed += (s32)(rsin(g_Task->unk_0C) << 0xD) >> 0xC;
    g_Task->pos.y.fixed += (s32)(rcos(g_Task->unk_0C) << 0xD) >> 0xC;
    value                      = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14             = value;
    COORD_INT(g_Task->pos.z) = (u16)COORD_INT(g_Task->pos.z) + value;
    if ((u8)g_Task->unk_09 < 8U) {
        value3 = g_Task->timer;
        if (value3 < 0x10U) {
            g_Task->timer = value3 + 1;
        }
    }
    value2         = g_Task->unk_09 - 1;
    g_Task->unk_09 = value2;
    if (!(value2 & 0xFF)) {
        g_Task->step += 1;
    }
}

#include "overlays/bmagic/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801EFFCC(void) {
    PartyBattler* work;
    PartyBattler* source;
    s8            temp_v0;
    u8            temp_v0_2;

    temp_v0 = (s8)g_Task->unk_5D;
    if (temp_v0 != -0x80) {
        g_Task->unk_5D = temp_v0 - 0x10;
        g_Task->unk_5E -= 0x10;
        g_Task->unk_5F -= 0x10;
    }
    temp_v0_2 = g_Task->timer;
    if (temp_v0_2 != 0) {
        g_Task->timer = temp_v0_2 - 2;
    }
    if ((s8)g_Task->unk_5D == -0x80) {
        work              = g_Task;
        source            = BATTLE_ACTIVE_WORK;
        work->pos.x.fixed = source->pos.x.fixed;
        work->pos.y.fixed = source->pos.y.fixed;
        work->pos.z.fixed = source->pos.z.fixed;
        work->step += 1;
    }
}

MATCH void func_801F00A8(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

INCLUDE_ASM(func_801F014C);

INCLUDE_ASM(func_801F0238);
