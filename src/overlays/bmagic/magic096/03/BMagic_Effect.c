#include "magic096_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC84(void) {
    u16* dst;
    u16* src;
    u32  i;
    u32  slot;

    func_801F0164();
    func_800AF764();
    TASK(PartyMember)->facing       = g_BattleEffectBattler->facing;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 8;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 16; i++) {
        slot                               = Battle_AllocEffect(1, 76) & BYTE_MASK;
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].arg.unk_09   = D_801F0498[i] + 1;
        g_BattleEffects[slot].unk_04       = i;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    do {
        *dst++ = *src++;
        i++;
    } while (i < AREA_PALETTE_COLORS);
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEDD8(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x200);
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEA0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE4(void) {
    Magic096Steps handlers = D_801EEC10;

    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801EF43C();
        func_801EF4FC();
        PopMatrix();
        Effect_SetActorMatrix();
        func_801EFB3C();
        BMagic_DrawGlowRing();
        PopMatrix();
    }
}

MATCH void func_801EEFB8(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
        TASK(PartyMember)->unk_0C = D_801F0408[TASK(PartyMember)->unk_04].x;
        TASK(PartyMember)->unk_10 = D_801F0408[TASK(PartyMember)->unk_04].y;
        Effect_RotatePosition(g_Task);
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + TASK(PartyMember)->unk_10;
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        switch (TASK(PartyMember)->facing) {
            case 0:
                if (!(TASK(PartyMember)->unk_04 & 1)) {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) + 0xE80;
                } else {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) + 0x80;
                }
                TASK(PartyMember)->unk_1C = ((rand() & 0xFF) - 0x80) & ANGLE_MASK;
                if (!(rand() & 0xF)) {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) - 0x80;
                }
                break;
            case 1:
                if (!(TASK(PartyMember)->unk_04 & 1)) {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) + 0xE80;
                } else {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) + 0x80;
                }
                TASK(PartyMember)->unk_18 = ((rand() & 0xFF) - 0x80) & ANGLE_MASK;
                if (!(rand() & 0xF)) {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) - 0x80;
                }
                break;
            case 2:
                if (TASK(PartyMember)->unk_04 & 1) {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) + 0xE80;
                } else {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) + 0x80;
                }
                TASK(PartyMember)->unk_1C = ((rand() & 0xFF) - 0x80) & ANGLE_MASK;
                if (!(rand() & 0xF)) {
                    TASK(PartyMember)->unk_18 = (rand() & 0xFF) - 0x80;
                }
                break;
            case 3:
                if (TASK(PartyMember)->unk_04 & 1) {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) + 0xE80;
                } else {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) + 0x80;
                }
                TASK(PartyMember)->unk_18 = ((rand() & 0xFF) - 0x80) & ANGLE_MASK;
                if (!(rand() & 0xF)) {
                    TASK(PartyMember)->unk_1C = (rand() & 0xFF) - 0x80;
                }
                break;
        }
        TASK(PartyMember)->param.unk_0B = 30 - D_801F0498[TASK(PartyMember)->unk_04];
        TASK(PartyMember)->unk_09       = 0;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF2CC(void) {
    TASK(PartyMember)->unk_09 += 2;
    TASK(PartyMember)->timer += 2;
    if (TASK(PartyMember)->unk_09 == D_801F0488[TASK(PartyMember)->unk_04]) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownTickerAndStep.h"

#include "overlays/bmagic/shared/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/shared/Effect_CountDownAndFinish.h"

MATCH void func_801EF43C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, TASK(PartyMember)->unk_18, TASK(PartyMember)->unk_1C, 0);
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

MATCH void func_801EF4FC(void) {
    POLY_FT3* tri;
    POLY_FT4* quad;
    long      depth;
    long      flag;
    s32       j;
    s32       tpage;
    s32       x;
    s32       y;

    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->unk_09 * 34;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * 24;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 6;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 * 9;
    for (j = 0; j < 4; j++) {
        if (j == 2) {
            continue;
        }
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = -g_ScratchPad.cells.halves[2];
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(j << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(j << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz = -g_ScratchPad.cells.halves[3];
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin((j + 1) << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos((j + 1) << 10), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz = -g_ScratchPad.cells.halves[3];
        x                         = (g_ScratchPadVectors[1].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[1].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        tri = (POLY_FT3*)g_GfxPrimCursor;
        SetPolyFT3(tri);
        setTPage(tri, TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 832, 256);
        setClut(tri, 0, 506);
        setUV3(tri, j * 64 + 32, 64, j * 64, 96, (j + 1) * 64 - 1, 96);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&tri->x0, (long*)&tri->x1, (long*)&tri->x2, &depth, &flag);
        g_ScratchPad.cells.halves[7] = 128 - j * 16;
        setRGB0(tri, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_FT3));
        setVector(&g_ScratchPadVectors[0], g_ScratchPadVectors[1].vx, g_ScratchPadVectors[1].vy, g_ScratchPadVectors[1].vz);
        setVector(&g_ScratchPadVectors[1], g_ScratchPadVectors[2].vx, g_ScratchPadVectors[2].vy, g_ScratchPadVectors[2].vz);
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(j << 10), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(j << 10), g_ScratchPad.cells.halves[1]), 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin((j + 1) << 10), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos((j + 1) << 10), g_ScratchPad.cells.halves[1]), 0);
        x     = (g_ScratchPadVectors[2].vx << 9) + TASK(PartyMember)->pos.x.fixed;
        y     = (g_ScratchPadVectors[2].vy << 9) + TASK(PartyMember)->pos.y.fixed;
        tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        quad = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(quad);
        setTPage(quad, TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 832, 256);
        setClut(quad, 0, 506);
        setUV4(quad, j * 64, 96, j * 64 + 152, 96, j * 64, 159, j * 64 + 152, 159);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                      &depth, &flag);
        setRGB0(quad, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_FT4));
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EFB3C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->timer * 16 + 16;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->timer * 9;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->timer * 7;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        GFX_STEP_TRIANGLE_FAN(i << 9, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6]);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* The glow ring scratch: the inner and outer radius and the inner-edge red and green, then the quad corners
 * (g_ScratchPadVectors). */
#define GLOW_RING_INNER g_ScratchPad.cells.halves[0]
#define GLOW_RING_OUTER g_ScratchPad.cells.halves[1]
#define GLOW_RING_RED   g_ScratchPad.cells.halves[6]
#define GLOW_RING_GREEN g_ScratchPad.cells.halves[7]

/* A ring of 8 additive quads around the effect position, from 16 times the effect timer (byte 0x0A) plus 16
 * out to plus 128, coloured at the inner edge and fading out. */
MATCH void BMagic_DrawGlowRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    GLOW_RING_INNER           = TASK(PartyMember)->timer * 16 + 16;
    GLOW_RING_OUTER           = TASK(PartyMember)->timer * 16 + 0x80;
    GLOW_RING_RED             = TASK(PartyMember)->timer * 9;
    GLOW_RING_GREEN           = TASK(PartyMember)->timer * 7;
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    g_ScratchPadVectors[2].vz = 0;
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;
    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_OUTER);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_OUTER);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_INNER);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_INNER);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        setRGB3(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801F0164(void) {
    u8 i;

    MAGIC096_SUM_X = MAGIC096_SUM_Y = MAGIC096_SUM_Z = MAGIC096_SUM_COUNT = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            if (Battle_SlotIsBlocked((u8)(i + 3)) == 0) {
                MAGIC096_SUM_X += (g_BattleEnemyBattlers[i].pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
                MAGIC096_SUM_Y += (g_BattleEnemyBattlers[i].pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
                MAGIC096_SUM_Z += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
                MAGIC096_SUM_COUNT += 1;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (Battle_SlotIsBlocked(i) == 0) {
                MAGIC096_SUM_X += (g_Game.members[i].pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
                MAGIC096_SUM_Y += (g_Game.members[i].pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
                MAGIC096_SUM_Z += COORD_INT(g_Game.members[i].pos.z);
                MAGIC096_SUM_COUNT += 1;
            }
        }
    }
    TASK(PartyMember)->pos.x.fixed      = (MAGIC096_SUM_X / MAGIC096_SUM_COUNT + AREA_CELL_ORIGIN) << 9;
    TASK(PartyMember)->pos.y.fixed      = (MAGIC096_SUM_Y / MAGIC096_SUM_COUNT + AREA_CELL_ORIGIN) << 9;
    COORD_INT(TASK(PartyMember)->pos.z) = MAGIC096_SUM_Z / MAGIC096_SUM_COUNT;
}
