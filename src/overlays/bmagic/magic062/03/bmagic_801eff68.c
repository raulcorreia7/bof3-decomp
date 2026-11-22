#include "magic062_03.h"
#include "menu/clock.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EFF68(void) {
    s32 value;
    s32 value2;
    u8  value3;

    Battle_ProjectRange();
    if ((BMAGIC_WORK->unk_0C == 4) && (BMAGIC_WORK->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0910(value2);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F026C);
    if (BMAGIC_WORK->unk_0C < 4) {
        value               = BMAGIC_WORK->unk_10 + 1;
        BMAGIC_WORK->unk_10 = value;
        if (!(value & 0x7)) {
            BMAGIC_WORK->unk_0C += 1;
        }
    }
    BMAGIC_WORK->unk_09 += BMAGIC_WORK->unk_0C;
    if (BMAGIC_WORK->unk_0C == 4) {
        value3             = BMAGIC_WORK->timer - 1;
        BMAGIC_WORK->timer = value3;
        if (!(value3 & BYTE_MASK)) {
            if (BMAGIC_WORK->param.unk_0B == 0) {
                SND_SEQueueSelection(0x101);
            }
            BMAGIC_WORK->unk_10 = 8;
            BMAGIC_WORK->unk_14 = 8;
            BMAGIC_WORK->unk_20 = 8;
            BMAGIC_WORK->header.step += 1;
        }
    }
}

MATCH void func_801F00EC(void) {
    s16* angle;
    u16  phase;
    u8   count;

    Battle_ProjectRange();
    func_801F0910(RANDOM_MASK(3) | 0x20);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F026C);
    BMAGIC_WORK->unk_10 += 4;
    BMAGIC_WORK->unk_09 += BMAGIC_WORK->unk_0C;
    phase                     = BMAGIC_WORK->param.unk_0B + 2;
    BMAGIC_WORK->param.unk_0B = phase;
    phase &= 0x1F;
    angle                    = &D_1F800004;
    *angle                   = phase << 7;
    g_ScratchPadHalves       = BMAGIC_WORK->timer * BMAGIC_WORK->unk_10 + 0xB0;
    BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(phase << 7) * g_ScratchPadHalves) >> 3);
    BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle) * g_ScratchPadHalves) >> 3);
    count                    = BMAGIC_WORK->timer + 1;
    BMAGIC_WORK->timer       = count;
    if (count == 0x10) {
        g_BattleEffectBattler->param.unk_0B--;
        Effect_Reset();
    }
}

MATCH void func_801F026C(void) {
    POLY_G3* prim;
    u8*      first;
    s32      x;
    s32      y;
    s32      depths[16];
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));
    first = g_GfxPrimCursor;
    for (i = BMAGIC_WORK->unk_09; i < BMAGIC_WORK->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[1] = 0x50;
        g_ScratchPad.cells.halves[0] = 0x30;
        g_ScratchPad.cells.halves[7] = (i - BMAGIC_WORK->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0BA4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0BA4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0BA4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[2] = (i & 0x1F) << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        g_ScratchPad.cells.halves[2] = ((i + 8) & 0x1F) << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - BMAGIC_WORK->unk_09) / 8] = RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = BMAGIC_WORK->pos.x.fixed;
    y = BMAGIC_WORK->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
    first = g_GfxPrimCursor;
    for (i = BMAGIC_WORK->unk_09; i < BMAGIC_WORK->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[7] = (i - BMAGIC_WORK->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0BD4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0BD4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0BD4[BMAGIC_WORK->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = -g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[2] = (i & 0x1F) << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        g_ScratchPad.cells.halves[2] = ((i + 8) & 0x1F) << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - BMAGIC_WORK->unk_09) / 8] = RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = BMAGIC_WORK->pos.x.fixed;
    y = BMAGIC_WORK->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
}

MATCH void func_801F0910(s32 shade) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = shade;
    g_ScratchPad.cells.halves[4] = D_801F0C04[BMAGIC_WORK->unk_04][0];
    g_ScratchPad.cells.halves[5] = D_801F0C04[BMAGIC_WORK->unk_04][1];
    g_ScratchPad.cells.halves[6] = D_801F0C04[BMAGIC_WORK->unk_04][2];
    for (i = 0; i < 8; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, BMAGIC_WORK->screen_x.value, BMAGIC_WORK->screen_y.value, BMAGIC_WORK->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               BMAGIC_WORK->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), BMAGIC_WORK->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               BMAGIC_WORK->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
