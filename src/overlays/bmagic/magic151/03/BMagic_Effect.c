#include "magic151_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EECB0);

MATCH void func_801EEDE0(void) {
    Callback handlers[2] = {func_801EEE38, func_801EF318};

    SYS_DISPATCH_TASK(handlers, 2, g_SpadWork);
}

MATCH void func_801EEE38(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.handlers, 3, g_SpadWork);
}

MATCH void func_801EEEA8(void) {
    PartyBattler* saved_work;
    PartyBattler* battler;

    saved_work = g_SpadWork;
    battler    = &g_BattlePartyBattlers[g_BattleActingBattler];
    g_SpadWork = battler;
    Actor_RequestScript((battler->word_08.byte.facing_08 + 0x3C) & 0xFF);
    g_SpadWork = saved_work;
    saved_work->unk_03 += 1;
}

INCLUDE_ASM(func_801EEF24);

INCLUDE_ASM(func_801EF070);

INCLUDE_ASM(func_801EF138);

MATCH void func_801EF2A0(void) {
    PartyBattler* saved_work;
    PartyBattler* battler;

    saved_work = g_SpadWork;
    battler    = &g_BattlePartyBattlers[g_BattleActingBattler];
    g_SpadWork = battler;
    battler->flags_00 &= 0xBF;
    g_SpadWork = saved_work;
    saved_work->step_01 += 1;
    g_SpadWork->unk_02 = 0;
    g_SpadWork->unk_03 = 0;
}

MATCH void func_801EF318(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC24;
    SYS_DISPATCH_TASK(handlers.handlers, 3, g_SpadWork);
}

INCLUDE_ASM(func_801EF388);

INCLUDE_ASM(func_801EF484);

INCLUDE_ASM(func_801EF938);

MATCH void func_801EF9F0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EFA34(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC38, unk_02);
}

INCLUDE_ASM(func_801EFAAC);

INCLUDE_ASM(func_801EFBAC);

INCLUDE_ASM(func_801EFC68);

MATCH void func_801EFD24(void) {
    u8 count;

    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02                      = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EFD80(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->step_01 == 2) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EFDC0(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        D_801EB4E0->word_08.byte.unk_0B = 2;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F24B8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F026C();
        func_801F0648();
        PopMatrix();
    }
}

MATCH void func_801EFE90(void) {
    PartyBattler* work  = g_SpadWork;
    PartyBattler* actor = D_801EB4E0;
    s32           z;

    work->coord_x_34.raw              = actor->coord_x_34.raw;
    work->coord_y_38.raw              = actor->coord_y_38.raw;
    z                                 = actor->word_3C.word;
    work->unk_5D                      = 0x10;
    work->word_3C.word                = z;
    g_SpadWork->unk_5E                = 0x10;
    g_SpadWork->unk_5F                = 0x24;
    g_SpadWork->unk_04                = 0;
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0x1E;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801EFF44(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 2;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EFF94);

#include "overlays/bmagic/Effect_StepOnZeroTick.h"

MATCH void func_801F00E8(void) {
    u8 temp_v1;

    temp_v1            = g_SpadWork->unk_5D - 1;
    g_SpadWork->unk_5D = temp_v1;
    if ((s8)temp_v1 == 8) {
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F013C(void) {
    s8 temp_v0;
    u8 temp_v0_2;

    temp_v0 = (s8)g_SpadWork->unk_5D;
    if (temp_v0 != 0) {
        g_SpadWork->unk_5D = temp_v0 - 1;
    }
    temp_v0_2          = g_SpadWork->unk_5E - 1;
    g_SpadWork->unk_5E = temp_v0_2;
    if ((temp_v0_2 << 0x18) == 0) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0648);

INCLUDE_ASM(func_801F0AC8);

MATCH void func_801F0BA8(void) {
    PartyBattler* work;
    s32           value;

    g_SpadWork->coord_x_34.raw        = D_801EB4E0->coord_x_34.raw;
    g_SpadWork->coord_y_38.raw        = D_801EB4E0->coord_y_38.raw;
    g_SpadWork->word_3C.word          = D_801EB4E0->word_3C.word;
    value                             = rand() & 0x1F;
    work                              = g_SpadWork;
    work->unk_5D                      = 0x10;
    work->unk_0C                      = value;
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 4;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801F0C50(void) {
    u8 temp_v0;

    temp_v0                           = g_SpadWork->word_08.byte.timer_0A + 4;
    g_SpadWork->word_08.byte.timer_0A = temp_v0;
    if ((u32)(temp_v0 & 0xFF) >= 0x20U) {
        g_SpadWork->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0CB0(void) {
    PartyBattler* work;
    s8            timer;

    work         = g_SpadWork;
    timer        = work->unk_5D - 2;
    work->unk_5D = timer;
    if (timer == 0) {
        work                      = D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0D0C);

INCLUDE_ASM(func_801F10E8);

MATCH void func_801F11E0(void) {
    u8 temp_v0;

    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->coord_x_34.raw        = D_801EB4E0->coord_x_34.raw;
        g_SpadWork->coord_y_38.raw        = D_801EB4E0->coord_y_38.raw;
        g_SpadWork->word_3C.word          = D_801EB4E0->word_3C.word;
        g_SpadWork->word_08.byte.unk_0B   = rand() & 0xF;
        g_SpadWork->word_08.byte.unk_09   = 0;
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F129C(void) {
    g_SpadWork->word_08.byte.unk_0B += 1;
    g_SpadWork->word_08.byte.timer_0A += 4;
    if (g_SpadWork->word_08.byte.timer_0A == 0x10) {
        g_SpadWork->word_08.byte.unk_09 = 8;
        g_SpadWork->unk_02 += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerRaiseTicker.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801F14D0);

MATCH void func_801F1C3C(void) {
    SYS_DISPATCH_BYTE(D_801F250C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        func_801F1DC0();
        func_801F1E70();
        func_801F2188();
        PopMatrix();
    }
}

MATCH void func_801F1CCC(void) {
    PartyBattler* work  = g_SpadWork;
    PartyBattler* actor = D_801EB4E0;
    s32           z;

    work->coord_x_34.raw      = actor->coord_x_34.raw;
    work->coord_y_38.raw      = actor->coord_y_38.raw;
    z                         = actor->word_3C.word;
    work->word_08.byte.unk_09 = 0x10;
    work->unk_14              = 0x100;
    work->word_3C.word        = z;
    g_SpadWork->unk_02 += 1;
}

MATCH void func_801F1D28(void) {
    PartyBattler* work;
    s32           value;

    work         = g_SpadWork;
    value        = work->unk_14 + 0x80;
    work->unk_14 = value;
    if (value == 0x400) {
        work->unk_02++;
    }
}

/* Best 7 differences: lui a0 at 0x801F1D60; adjust register allocation. */
/* Exact twin of magic125 func_801EF148; first difference there is lui v0 at entry. */
INCLUDE_ASM(func_801F1D60);

MATCH void Effect_SetActorMatrix_801F1DC0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

INCLUDE_ASM(func_801F1E70);

INCLUDE_ASM(func_801F2188);
