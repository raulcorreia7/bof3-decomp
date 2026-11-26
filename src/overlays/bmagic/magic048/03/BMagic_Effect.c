#include "magic048_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    u8           i;

    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->unk_09 = 10;
    SELF(PartyMember)->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 30) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = ((i ^ 0xF) - 3) * 8;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_08       = SELF(PartyMember)->facing;
        SELF(PartyMember)->param.unk_0B += 1;
        i++;
    } while (i < 12);
}

#include "overlays/bmagic/shared/Effect_CountDownTimerQueueEffect.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE70 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEB4(void) {
    SYS_DISPATCH_BYTE(D_801EF81C, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.step != 0 && SELF(PartyMember)->header.flags != 0) {
        func_801EF5C8();
        func_801EF234();
        PopMatrix();
    }
}

MATCH s32 func_801EEF3C(void) {
    PartyMember* work;
    FAKE_REG(s32, scroll, "a1"); /* FAKE: pins the scroll offset to retail a1; the best plain form differs in 6 instructions (scroll and battler registers). */
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        func_801EF6A0();
        SELF(PartyMember)->unk_0C = 0x10000;
        SELF(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
        SELF(PartyMember)->unk_0C      = 0x80000;
        SELF(PartyMember)->unk_10      = 0;
        Effect_RotatePosition(g_Self);
        work = SELF(PartyMember);
        work->unk_0C += g_AreaScrollTargetX;
        FAKE_BARRIER(); /* FAKE: keeps the height read below the velocity store. */
        work->unk_14 = COORD_INT(work->pos.z) + 0x100;
        scroll       = g_AreaScrollTargetY;
        work->unk_10 += scroll;
        COORD_INT(work->pos.z)   = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        work->unk_09             = 0;
        SELF(PartyMember)->timer = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF05C(void) {
    VECTOR pos;

    SELF(PartyMember)->unk_09 += 1;
    setVector(&pos, (SELF(PartyMember)->unk_0C >> 9) - AREA_CELL_ORIGIN, (SELF(PartyMember)->unk_10 >> 9) - AREA_CELL_ORIGIN, SELF(PartyMember)->unk_14 >> 1);
    Battle_StepRangeToward(pos, 0x10);
    if (SELF(PartyMember)->timer != 16) {
        SELF(PartyMember)->timer += 1;
    }
    if (func_800AF6B8(SELF(PartyMember)->unk_0C, SELF(PartyMember)->unk_10, SELF(PartyMember)->pos.z.fixed, 0x60000) != 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF158(void) {
    VECTOR pos;
    u8     count;

    setVector(&pos, (SELF(PartyMember)->unk_0C >> 9) - AREA_CELL_ORIGIN, (SELF(PartyMember)->unk_10 >> 9) - AREA_CELL_ORIGIN, SELF(PartyMember)->unk_14 >> 1);
    Battle_StepRangeToward(pos, 0x10);
    SELF(PartyMember)->unk_09 = SELF(PartyMember)->unk_09 + 1;
    count                     = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer  = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* Draw the magic048 ring as 32 shaded quads standing between two radii round the effect,
 * tinted at the outer edge by the timer; past a radius of 9 the outer edge flickers. */
MATCH void func_801EF234(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 4;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->unk_09 * 6;
    if (SELF(PartyMember)->unk_09 >= 9) {
        g_ScratchPad.cells.halves[2] += rand() & 0xF;
    }
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 4;
    /* FAKE: the first corner through the scratchpad view keeps the base register on the second corner, as retail does; through g_ScratchPadVectors it moves to the first. */
    g_ScratchPad.vectors[0].vx   = 0;
    setVector(&g_ScratchPadVectors[1], 0, FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]), FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]));
    g_ScratchPadVectors[2].vx = 0;
    setVector(&g_ScratchPadVectors[3], 0, FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]), FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]));
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[1].vz = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[2]);
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF5C8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, ratan2(SELF(PartyMember)->unk_10 - SELF(PartyMember)->pos.y.fixed, SELF(PartyMember)->unk_0C - SELF(PartyMember)->pos.x.fixed) & ANGLE_MASK);
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

MATCH void func_801EF6A0(void) {
    u8   i;
    s32* sum;
    s32* enemy_sum;
    s32* party_sum;

    /* The effect takes the mean z of the unblocked battlers on the targeted side; the scratchpad keeps the sum and the count. */
    sum                         = &g_ScratchPad.cells.words[0];
    g_ScratchPad.cells.words[1] = 0;
    *sum                        = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        i         = 0;
        enemy_sum = sum;
        for (; i < 8; i++) {
            if (!Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT))) {
                enemy_sum[0] += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
                enemy_sum[1] += 1;
            }
        }
    } else {
        i         = 0;
        party_sum = sum;
        for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                party_sum[0] += COORD_INT(g_Game.members[i].pos.z);
                party_sum[1] += 1;
            }
        }
    }
    COORD_INT(SELF(PartyMember)->pos.z) = g_ScratchPad.cells.words[0] / g_ScratchPad.cells.words[1];
}
