#include "magic096_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC84);

MATCH void func_801EEDD8(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x200);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEEA0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

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

INCLUDE_ASM(func_801EEFB8);

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

INCLUDE_ASM(func_801EF4FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EFB3C);

/* The glow ring scratch: the inner and outer radius and the inner-edge red and green, then the quad corners
 * (D_1F800014). */
#define GLOW_RING_INNER D_1F800000_HALF[0]
#define GLOW_RING_OUTER D_1F800000_HALF[1]
#define GLOW_RING_RED   D_1F800000_HALF[6]
#define GLOW_RING_GREEN D_1F800000_HALF[7]

/* A ring of 8 additive quads around the effect position, from 16 times the effect timer (byte 0x0A) plus 16
 * out to plus 128, coloured at the inner edge and fading out. */
MATCH void BMagic_DrawGlowRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, 0xC);
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
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 9), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 9), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        setRGB3(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_RED);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, 0x24);
    }
}

INCLUDE_ASM(func_801F0164);
