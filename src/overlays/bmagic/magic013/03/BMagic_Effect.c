#include "magic013_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC14);

INCLUDE_ASM(func_801EED28);

MATCH void func_801EEE68(void) {
    PartyBattler* work;
    u8            step;

    work = SP_REF(PartyBattler*, 0x44u);
    step = work->unk_0B;
    if (step < 2) {
        work->step_01 = work->step_01 + 1;
    }
}

MATCH void func_801EEEA0(void) {
    u8*           selector;
    u32           slot;
    PartyBattler* work;

    selector = (u8*)&g_BattleTargetSelector;
    if (!(Battle_SlotIsBlocked(*selector) & 0xFF) && (func_800AED5C(1, *selector) & 0xFF)) {
        slot                                = Battle_AllocEffect(1, 0x48) & BYTE_MASK;
        work                                = g_SpadWork;
        g_BattleEffects[slot].unk_04        = 4;
        g_BattleEffects[slot].unk_09        = 0x18;
        g_BattleEffects[slot].unk_0A        = 4;
        g_BattleEffects[slot].work_74.party = work;
        g_SpadWork->unk_0B += 1;
    }
    g_SpadWork->step_01 += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH void func_801EEFD0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(D_801F03C0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        func_801EF4F0();
        func_801EF79C();
        PopMatrix();
        func_801EF648();
        func_801EFAA8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF0A4);

MATCH void func_801EF1A0(void) {
    u8 timer;

    timer              = g_SpadWork->unk_04 + 2;
    g_SpadWork->unk_04 = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF1F0);

INCLUDE_ASM(func_801EF36C);

MATCH void func_801EF484(void) {
    PartyBattler* work;
    PartyBattler* active;

    work = g_SpadWork;
    if (work->unk_0B == 0) {
        work->unk_04 = work->unk_04 - 1;
        if (work->unk_04 == 0) {
            active         = BATTLE_ACTIVE_WORK;
            active->unk_0B = active->unk_0B - 1;
            func_801E5988();
        }
    }
}

INCLUDE_ASM(func_801EF4F0);

INCLUDE_ASM(func_801EF648);

INCLUDE_ASM(func_801EF79C);

INCLUDE_ASM(func_801EFAA8);

MATCH void func_801EFDB4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 7), 1, g_SpadWork);
}

MATCH void func_801EFDF8(void) {
    SYS_DISPATCH_BYTE(D_801F03DC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_09 != 0) {
        func_801F00A8();
        func_801F0164();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EFE80);

INCLUDE_ASM(func_801EFF88);

MATCH void func_801F00A8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_SpadWork->unk_09 << 6;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801F0164);

/* func_801F0358 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
