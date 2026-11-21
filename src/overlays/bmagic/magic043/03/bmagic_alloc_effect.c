#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EF42C(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0x20000;
        g_Task->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
        g_Task->unk_0C      = -0x1000;
        g_Task->unk_10      = 0;
        Effect_RotatePosition(g_Task);
        g_Task->unk_14 = ratan2(g_BattleEffectBattler->pos.x.fixed - g_AreaScrollTargetX, g_BattleEffectBattler->pos.y.fixed - g_AreaScrollTargetY);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF55C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer += 2;
    if (g_Task->timer == 16) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF5E0(void) {
    PartyMember* work;
    u8           count;

    work         = g_Task;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 24) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF64C(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    if (g_Task->timer == 0) {
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
    setVector(&rot, 1024, D_801EFC9C[g_Task->facing], 0);
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF7F8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    SPAD(0u)->cells.halves[0] = g_Task->timer * 16 + 16;
    SPAD(0u)->cells.halves[1] = g_Task->timer * 16 + 0x80;
    SPAD(0u)->cells.halves[3] = g_Task->timer * 9;
    SPAD(0u)->cells.halves[4] = g_Task->timer * 7;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), SPAD(0u)->cells.halves[1]);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), SPAD(0u)->cells.halves[1]);
    g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), SPAD(0u)->cells.halves[0]);
    g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), SPAD(0u)->cells.halves[0]);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 9), SPAD(0u)->cells.halves[1]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 9), SPAD(0u)->cells.halves[1]);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 9), SPAD(0u)->cells.halves[0]);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 9), SPAD(0u)->cells.halves[0]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, SPAD(0u)->cells.halves[3], SPAD(0u)->cells.halves[4], SPAD(0u)->cells.halves[5]);
        setRGB3(prim, SPAD(0u)->cells.halves[3], SPAD(0u)->cells.halves[4], SPAD(0u)->cells.halves[5]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}
#else
INCLUDE_ASM(func_801EF7F8);
#endif

/* func_801EFC24 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
