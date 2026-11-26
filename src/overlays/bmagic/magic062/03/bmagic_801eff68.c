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
    if ((SELF(PartyMember)->unk_0C == 4) && (SELF(PartyMember)->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0910(value2);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F026C);
    if (SELF(PartyMember)->unk_0C < 4) {
        value                     = SELF(PartyMember)->unk_10 + 1;
        SELF(PartyMember)->unk_10 = value;
        if (!(value & 0x7)) {
            SELF(PartyMember)->unk_0C += 1;
        }
    }
    SELF(PartyMember)->unk_09 += SELF(PartyMember)->unk_0C;
    if (SELF(PartyMember)->unk_0C == 4) {
        value3                   = SELF(PartyMember)->timer - 1;
        SELF(PartyMember)->timer = value3;
        if (!(value3 & BYTE_MASK)) {
            if (SELF(PartyMember)->param.unk_0B == 0) {
                SND_SEQueueSelection(0x101);
            }
            SELF(PartyMember)->unk_10 = 8;
            SELF(PartyMember)->unk_14 = 8;
            SELF(PartyMember)->unk_20 = 8;
            SELF(PartyMember)->header.step += 1;
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
    SELF(PartyMember)->unk_10 += 4;
    SELF(PartyMember)->unk_09 += SELF(PartyMember)->unk_0C;
    phase                           = SELF(PartyMember)->param.unk_0B + 2;
    SELF(PartyMember)->param.unk_0B = phase;
    phase &= 0x1F;
    angle                          = &D_1F800004;
    *angle                         = phase << 7;
    g_ScratchPadHalves             = SELF(PartyMember)->timer * SELF(PartyMember)->unk_10 + 0xB0;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(phase << 7) * g_ScratchPadHalves) >> 3);
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle) * g_ScratchPadHalves) >> 3);
    count                          = SELF(PartyMember)->timer + 1;
    SELF(PartyMember)->timer       = count;
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
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    first = g_GfxPrimCursor;
    for (i = SELF(PartyMember)->unk_09; i < SELF(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[1] = 0x50;
        g_ScratchPad.cells.halves[0] = 0x30;
        g_ScratchPad.cells.halves[7] = (i - SELF(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0BA4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0BA4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0BA4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
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
        depths[(i - SELF(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = SELF(PartyMember)->pos.x.fixed;
    y = SELF(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
    first = g_GfxPrimCursor;
    for (i = SELF(PartyMember)->unk_09; i < SELF(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[7] = (i - SELF(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0BD4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0BD4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0BD4[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
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
        depths[(i - SELF(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = SELF(PartyMember)->pos.x.fixed;
    y = SELF(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
}

MATCH void func_801F0910(s32 shade) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = shade;
    g_ScratchPad.cells.halves[4] = D_801F0C04[SELF(PartyMember)->unk_04][0];
    g_ScratchPad.cells.halves[5] = D_801F0C04[SELF(PartyMember)->unk_04][1];
    g_ScratchPad.cells.halves[6] = D_801F0C04[SELF(PartyMember)->unk_04][2];
    for (i = 0; i < 8; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]),
               SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
