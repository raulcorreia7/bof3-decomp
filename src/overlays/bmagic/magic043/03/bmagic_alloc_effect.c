#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EF42C(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
        TASK(PartyMember)->unk_0C = 0x20000;
        TASK(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + TASK(PartyMember)->unk_10;
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
        TASK(PartyMember)->unk_0C      = -0x1000;
        TASK(PartyMember)->unk_10      = 0;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->unk_14 = ratan2(g_BattleEffectBattler->pos.x.fixed - g_AreaScrollTargetX, g_BattleEffectBattler->pos.y.fixed - g_AreaScrollTargetY);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->timer  = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF55C(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->timer += 2;
    if (TASK(PartyMember)->timer == 16) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF5E0(void) {
    PartyMember* work;
    u8           count;

    work         = TASK(PartyMember);
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 24) {
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF64C(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->timer -= 2;
    if (TASK(PartyMember)->timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        BMagic_ResetLocalWork();
    }
}

MATCH void func_801EF72C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 1024, D_801EFC9C[TASK(PartyMember)->facing], 0);
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF7F8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 8;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 * 12;
    if (g_Battle.action_id == 0x2B) {
        g_ScratchPad.cells.halves[3] = (RANDOM_MASK(7) + 4) * TASK(PartyMember)->timer;
        g_ScratchPad.cells.halves[4] = (RANDOM_MASK(7) + 4) * TASK(PartyMember)->timer;
        g_ScratchPad.cells.halves[5] = (RANDOM_MASK(7) + 4) * TASK(PartyMember)->timer;
    } else {
        g_ScratchPad.cells.halves[3] = TASK(PartyMember)->timer * 4;
        g_ScratchPad.cells.halves[4] = TASK(PartyMember)->timer * 8;
        g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 4;
    }
    g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vz = 0;
    g_ScratchPadVectors[2].vz = 0;
    for (i = 1; i <= 8; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
    }
}
#else
INCLUDE_ASM(func_801EF7F8);
#endif

/* func_801EFC24 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
