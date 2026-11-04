#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED38};

    table[SP_REF(u8*, 0x44)[1]]();
}

MATCH void func_801EEC5C(void) {
    u8            i;
    u32           slot;
    PartyBattler* work;

    g_SpadWork->unk_0B = 0;
    for (i = 0; i < 4; i++) {
        slot                                = Battle_AllocEffect(1, 0x2B) & BYTE_MASK;
        work                                = g_SpadWork;
        g_BattleEffects[slot].unk_01        = i;
        g_BattleEffects[slot].unk_02        = 0;
        g_BattleEffects[slot].unk_09        = 0x10;
        g_BattleEffects[slot].work_74.party = work;
        g_SpadWork->unk_0B                  = g_SpadWork->unk_0B + 1;
    }
    SND_QueueSelectionFx(0x100);
    g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EED98(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

MATCH void func_801EEDDC(void) {
    SYS_DISPATCH_BYTE(D_801F02B4, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEE64);

INCLUDE_ASM(func_801EEEE4);

INCLUDE_ASM(func_801EEF34);

INCLUDE_ASM(func_801EEFB8);

MATCH void func_801EF048(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_0A = work->unk_0A - 1;
    work         = g_SpadWork;
    work->unk_0B = work->unk_0B - 1;
    if (work->unk_0B == 0) {
        func_801E5988();
    }
}

MATCH void func_801EF0A8(void) {
    SYS_DISPATCH_BYTE(D_801F02C8, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801EF458();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF130);

INCLUDE_ASM(func_801EF1DC);

INCLUDE_ASM(func_801EF23C);

INCLUDE_ASM(func_801EF2BC);

MATCH void func_801EF348(void) {
    PartyBattler* work;

    work         = g_SpadWork;
    work->unk_0A = work->unk_0A + 1;
    work         = g_SpadWork;
    work->unk_0B = work->unk_0B - 1;
    if (work->unk_0B == 0) {
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF458);

MATCH void func_801EFBEC(void) {
    SYS_DISPATCH_BYTE(D_801F035C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

MATCH void func_801EFC74(void) {
    PartyBattler* src;

    src                    = g_BattleSelectedActor;
    g_SpadWork->coord_x_34 = src->coord_x_34;
    g_SpadWork->coord_y_38 = src->coord_y_38;
    g_SpadWork->word_3C    = src->word_3C;
    g_SpadWork->unk_09     = 4;
    g_SpadWork->unk_0A     = 0xB0;
    g_SpadWork->unk_02     = g_SpadWork->unk_02 + 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

INCLUDE_ASM(func_801EFD2C);

MATCH void func_801EFD84(void) {
    PartyBattler* work;
    PartyBattler* active;

    work         = g_SpadWork;
    work->unk_0A = work->unk_0A - 1;
    work         = g_SpadWork;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = active->unk_0B - 1;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F036C, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->unk_02 != 0) {
        Effect_SetActorMatrix();
        func_801F002C();
        PopMatrix();
    }
}

/* Counts unk_09 down; at 0 copies coord_x_34, coord_y_38 and word_3C from D_8014637C, sets unk_09 = 4 and steps.
 * The Effect_CopyBattlerCoords shape with a work local and a reloaded g_SpadWork for the step matches the bytes with
 * (PartyBattler*)D_8014637C; needs: type D_8014637C PartyBattler* (it is u8* in slus/data.h; battle/battle/03 indexes it
 * as bytes at 5 sites and casts it at 4). */
INCLUDE_ASM(func_801EFE88);

MATCH void Effect_CountUpAndStep_801EFF08(void) {
    u8 timer;

    BMAGIC_COUNT_UP_AND_STEP();
}

INCLUDE_ASM(func_801EFF58);

MATCH void func_801EFFB0(void) {
    PartyBattler* work;
    PartyBattler* active;

    work         = g_SpadWork;
    work->unk_0A = work->unk_0A + 1;
    work         = g_SpadWork;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 4) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = active->unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F002C);
