#include "magic118_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC18 */
MATCH void BMagic_UpdateBurn(void) {
    Magic118Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawBurnFlameQuads();
        BMagic_DrawBurnFlameTris();
        PopMatrix();
    }
}

INCLUDE_ASM(BMagic_SpawnBurnFlames);

/* func_801EEE20 */
MATCH void BMagic_SelectBurnTarget(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnWorkLastTick.h"

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF6C */
MATCH void BMagic_UpdateBurnSprites(void) {
    SYS_DISPATCH_BYTE(D_801EFCD4, g_Task->header.mode);
    if (g_Task->header.flags != 0 && g_Task->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawBurnSprites();
        PopMatrix();
    }
}

/* Retail keeps the battler in v1 and the task in a0; the draft (--dec form, timer 2, unk_14 zero) is one instruction short at the 0x14 bnez, the reg order differs. */
INCLUDE_ASM(func_801EEFF4);

/* blocker: sum register; first diff: lw a0,0x20($v1) (retail) against lw v0,0x20($v1). */
/* blocker: timer and unk_20 load order; first diff: lbu a1 against v0 at 0x801EF0B0. */
INCLUDE_ASM(func_801EF0A4);

MATCH void func_801EF108(void) {
    PartyBattler* work;
    u8            timer;

    g_Task->param.unk_0B--;
    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_20 += work->timer;
    work->unk_14 += work->unk_20;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(BMagic_DrawBurnSprites);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* The dark ring scratch: the inner and outer radius and the inner-edge shade, then the quad corners
 * (D_1F800014). */
#define DARK_RING_INNER D_1F800000_HALF[1]
#define DARK_RING_OUTER D_1F800000_HALF[2]
#define DARK_RING_SHADE D_1F800000_HALF[5]

/* A ring of 32 subtractive quads from radius 128 to 192 that darkens toward its inner edge by six times the
 * effect counter (byte 0x09), then the draw mode back to plain blending. */
MATCH void BMagic_DrawBurnFlameQuads(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    GFX_AddPrim(5, 0xC);
    DARK_RING_INNER  = 0x80;
    DARK_RING_OUTER  = 0xC0;
    DARK_RING_SHADE  = g_Task->unk_09 * 6;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), DARK_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), DARK_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), DARK_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), DARK_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 7), DARK_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 7), DARK_RING_OUTER);
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 7), DARK_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 7), DARK_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, DARK_RING_SHADE, DARK_RING_SHADE, DARK_RING_SHADE);
        setRGB3(prim, DARK_RING_SHADE, DARK_RING_SHADE, DARK_RING_SHADE);
        GFX_AddPrim(5, 0x24);
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, 320, 256), 0);
    GFX_AddPrim(5, 0xC);
}

INCLUDE_ASM(BMagic_DrawBurnFlameTris);
