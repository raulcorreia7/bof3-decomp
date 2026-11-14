#include "magic096_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC84(void) {
    u16* dst;
    u16* src;
    u32  i;
    u32  slot;

    func_801F0164();
    func_800AF764();
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 8;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 16; i++) {
        slot                               = Battle_AllocEffect(1, 76) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].arg.unk_09   = D_801F0498[i] + 1;
        g_BattleEffects[slot].unk_04       = i;
        g_Task->param.unk_0B += 1;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    do {
        *dst++ = *src++;
        i++;
    } while (i < 256);
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(0x100);
}

MATCH void func_801EEDD8(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x200);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEA0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE4(void) {
    Magic096Steps handlers = D_801EEC10;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
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

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = D_801F0408[g_Task->unk_04].x;
        g_Task->unk_10 = D_801F0408[g_Task->unk_04].y;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        switch (g_Task->facing) {
            case 0:
                if (!(g_Task->unk_04 & 1)) {
                    g_Task->unk_18 = (rand() & 0xFF) + 0xE80;
                } else {
                    g_Task->unk_18 = (rand() & 0xFF) + 0x80;
                }
                g_Task->unk_1C = ((rand() & 0xFF) - 0x80) & 0xFFF;
                if (!(rand() & 0xF)) {
                    g_Task->unk_18 = (rand() & 0xFF) - 0x80;
                }
                break;
            case 1:
                if (!(g_Task->unk_04 & 1)) {
                    g_Task->unk_1C = (rand() & 0xFF) + 0xE80;
                } else {
                    g_Task->unk_1C = (rand() & 0xFF) + 0x80;
                }
                g_Task->unk_18 = ((rand() & 0xFF) - 0x80) & 0xFFF;
                if (!(rand() & 0xF)) {
                    g_Task->unk_1C = (rand() & 0xFF) - 0x80;
                }
                break;
            case 2:
                if (g_Task->unk_04 & 1) {
                    g_Task->unk_18 = (rand() & 0xFF) + 0xE80;
                } else {
                    g_Task->unk_18 = (rand() & 0xFF) + 0x80;
                }
                g_Task->unk_1C = ((rand() & 0xFF) - 0x80) & 0xFFF;
                if (!(rand() & 0xF)) {
                    g_Task->unk_18 = (rand() & 0xFF) - 0x80;
                }
                break;
            case 3:
                if (g_Task->unk_04 & 1) {
                    g_Task->unk_1C = (rand() & 0xFF) + 0xE80;
                } else {
                    g_Task->unk_1C = (rand() & 0xFF) + 0x80;
                }
                g_Task->unk_18 = ((rand() & 0xFF) - 0x80) & 0xFFF;
                if (!(rand() & 0xF)) {
                    g_Task->unk_1C = (rand() & 0xFF) - 0x80;
                }
                break;
        }
        g_Task->param.unk_0B = 30 - D_801F0498[g_Task->unk_04];
        g_Task->unk_09       = 0;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF2CC(void) {
    g_Task->unk_09 += 2;
    g_Task->timer += 2;
    if (g_Task->unk_09 == D_801F0488[g_Task->unk_04]) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTickerAndStep.h"

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/Effect_CountDownAndFinish.h"

MATCH void func_801EF43C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = g_Task->unk_18;
    rot.vy = g_Task->unk_1C;
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
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

    D_1F800000.view.effect.params[2] = g_Task->unk_09 * 34;
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 24;
    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 6;
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 9;
    for (j = 0; j < 4; j++) {
        if (j == 2) {
            continue;
        }
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[0].vz = -D_1F800000.view.effect.params[2];
        D_1F800014[1].vx = FIXED_MUL(rsin(j << 10), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(j << 10), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = -D_1F800000.view.effect.params[3];
        D_1F800014[2].vx = FIXED_MUL(rsin((j + 1) << 10), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos((j + 1) << 10), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = -D_1F800000.view.effect.params[3];
        x                = (D_1F800014[1].vx << 9) + g_Task->pos.x.fixed;
        y                = (D_1F800014[1].vy << 9) + g_Task->pos.y.fixed;
        tpage            = GetGraphType() == 1 || GetGraphType() == 2 ? 0x225 : 0x95;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        tri = (POLY_FT3*)g_GfxPrimCursor;
        SetPolyFT3(tri);
        setTPage(tri, 1, 0, 832, 256);
        setClut(tri, 0, 506);
        tri->u0 = j * 64 + 32;
        tri->v0 = 64;
        tri->u1 = j * 64;
        tri->v1 = 96;
        tri->u2 = (j + 1) * 64 - 1;
        tri->v2 = 96;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&tri->x0, (long*)&tri->x1, (long*)&tri->x2, &depth, &flag);
        D_1F800000.view.effect.params[7] = 128 - j * 16;
        setRGB0(tri, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7]);
        Area_AddCellPrim(x, y, 0, sizeof(POLY_FT3));
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = D_1F800014[1].vz;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[1].vz = D_1F800014[2].vz;
        D_1F800014[2].vx = FIXED_MUL(rsin(j << 10), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vy = FIXED_MUL(rcos(j << 10), D_1F800000.view.effect.params[1]);
        D_1F800014[2].vz = 0;
        D_1F800014[3].vx = FIXED_MUL(rsin((j + 1) << 10), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vy = FIXED_MUL(rcos((j + 1) << 10), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz = 0;
        x                = (D_1F800014[2].vx << 9) + g_Task->pos.x.fixed;
        y                = (D_1F800014[2].vy << 9) + g_Task->pos.y.fixed;
        tpage            = GetGraphType() == 1 || GetGraphType() == 2 ? 0x225 : 0x95;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        quad = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(quad);
        setTPage(quad, 1, 0, 832, 256);
        setClut(quad, 0, 506);
        quad->u0 = j * 64;
        quad->v0 = 96;
        quad->u1 = j * 64 + 152;
        quad->v1 = 96;
        quad->u2 = j * 64;
        quad->v2 = 159;
        quad->u3 = j * 64 + 152;
        quad->v3 = 159;
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3, &depth, &flag);
        setRGB0(quad, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7]);
        Area_AddCellPrim(x, y, 0, sizeof(POLY_FT4));
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EFB3C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->timer * 16 + 16;
    D_1F800000.view.effect.params[5] = g_Task->timer * 8;
    D_1F800000.view.effect.params[6] = g_Task->timer * 9;
    D_1F800000.view.effect.params[7] = g_Task->timer * 7;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;
    for (i = 1; i <= 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[5]);
        setRGB1(prim, D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[6]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* The glow ring scratch: the inner and outer radius and the inner-edge red and green, then the quad corners
 * (D_1F800014). */
#define GLOW_RING_INNER D_1F800000.view.effect.params[0]
#define GLOW_RING_OUTER D_1F800000.view.effect.params[1]
#define GLOW_RING_RED   D_1F800000.view.effect.params[6]
#define GLOW_RING_GREEN D_1F800000.view.effect.params[7]

/* A ring of 8 additive quads around the effect position, from 16 times the effect timer (byte 0x0A) plus 16
 * out to plus 128, coloured at the inner edge and fading out. */
MATCH void BMagic_DrawGlowRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    GLOW_RING_INNER  = g_Task->timer * 16 + 16;
    GLOW_RING_OUTER  = g_Task->timer * 16 + 0x80;
    GLOW_RING_RED    = g_Task->timer * 9;
    GLOW_RING_GREEN  = g_Task->timer * 7;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 8; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        setRGB3(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801F0164(void) {
    u8 i;

    MAGIC096_SUM_X = MAGIC096_SUM_Y = MAGIC096_SUM_Z = MAGIC096_SUM_COUNT = 0;
    if (g_Battle.target_selector & 0x40) {
        for (i = 0; i < 8; i++) {
            if (Battle_SlotIsBlocked((u8)(i + 3)) == 0) {
                MAGIC096_SUM_X += (g_BattleEnemyBattlers[i].pos.x.fixed >> 9) - 0x4000;
                MAGIC096_SUM_Y += (g_BattleEnemyBattlers[i].pos.y.fixed >> 9) - 0x4000;
                MAGIC096_SUM_Z += COORD_INT(g_BattleEnemyBattlers[i].pos.z);
                MAGIC096_SUM_COUNT += 1;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (Battle_SlotIsBlocked(i) == 0) {
                MAGIC096_SUM_X += (g_Game.members[i].pos.x.fixed >> 9) - 0x4000;
                MAGIC096_SUM_Y += (g_Game.members[i].pos.y.fixed >> 9) - 0x4000;
                MAGIC096_SUM_Z += COORD_INT(g_Game.members[i].pos.z);
                MAGIC096_SUM_COUNT += 1;
            }
        }
    }
    g_Task->pos.x.fixed      = (MAGIC096_SUM_X / MAGIC096_SUM_COUNT + 0x4000) << 9;
    g_Task->pos.y.fixed      = (MAGIC096_SUM_Y / MAGIC096_SUM_COUNT + 0x4000) << 9;
    COORD_INT(g_Task->pos.z) = MAGIC096_SUM_Z / MAGIC096_SUM_COUNT;
}
