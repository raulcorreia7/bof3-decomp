#include "magic082_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F00DC(void) {
    s32 value;
    s32 value2;
    u8  value3;

    Battle_ProjectRange();
    if ((SELF(PartyMember)->unk_0C == 4) && (SELF(PartyMember)->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    BMagic_SetXFixed(value2);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
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

MATCH void func_801F0260(void) {
    s16* angle;
    u16  phase;
    u8   count;

    Battle_ProjectRange();
    BMagic_SetXFixed(RANDOM_MASK(3) | 0x20);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
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

/* Draw the magic082 shell as two fans of four flat triangles, one above and one below the
 * effect, each shaded from its colour table and linked into the map cell by depth. */
MATCH void func_801F03E0(void) {
    POLY_G3* prim;
    u8*      base;
    long     depth;
    long     flag;
    s32      values[16];
    s32      i;
    s32      tpage;
    s32      x;
    s32      y;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    base = g_GfxPrimCursor;
    for (i = SELF(PartyMember)->unk_09; i < SELF(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[1] = 0x50;
        g_ScratchPad.cells.halves[0] = 0x30;
        g_ScratchPad.cells.halves[7] = (i - SELF(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0C9C[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0C9C[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0C9C[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
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
        values[(i - SELF(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = SELF(PartyMember)->pos.x.fixed;
    y = SELF(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, values, base, 4, sizeof(POLY_G3), 2);
    base = g_GfxPrimCursor;
    for (i = SELF(PartyMember)->unk_09; i < SELF(PartyMember)->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[7] = (i - SELF(PartyMember)->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0CCC[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0CCC[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0CCC[SELF(PartyMember)->unk_04][g_ScratchPad.cells.halves[7]][2];
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
        values[(i - SELF(PartyMember)->unk_09) / 8] =
            RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = SELF(PartyMember)->pos.x.fixed;
    y = SELF(PartyMember)->pos.y.fixed;
    func_800AF0F8(x, y, values, base, 4, sizeof(POLY_G3), 2);
}

/* Draws a semi-transparent disc of the given radius round the effect's screen point as eight
 * shaded triangles, bright at the centre and dark at the rim. */
/* Sets the battle magic x position in fixed point. */
/* func_801F0A84 */
MATCH void BMagic_SetXFixed(s32 radius) {
    POLY_G3* prim;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.halves[0] = radius;
    i                            = 0;
    do {
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
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}
