#include "magic044_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEDA0);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u32          i;
    u8           slot;

    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 6) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    i   = 1;
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i + AREA_PALETTE_UNIT / sizeof(u16)] = src[i + AREA_PALETTE_UNIT / sizeof(u16)] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + AREA_PALETTE_UNIT) = 0;

    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE00 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE44(void) {
    SYS_DISPATCH_BYTE(D_801F0A1C, g_Task->header.step);
    if (g_Task->unk_04 != 0) {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EF4E0();
        }
    } else {
        if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
            func_801EFA4C();
        }
    }
}

INCLUDE_ASM(func_801EEEFC);

INCLUDE_ASM(func_801EF138);

MATCH void func_801EF320(void) {
    PartyMember* work;
    u32          slot;
    u8           count;

    if (g_Task->timer < 0x10) {
        g_Task->param.unk_0B += 1;
        g_Task->timer += 1;
        Battle_ProjectRange();
        Effect_RecordTrail();
    }
    if ((g_FrameCount & 0x3) == 0) {
        slot = Battle_AllocEffect(1, 6) & BYTE_MASK;
        if (slot != GAME_NONE) {
            work                               = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].target.party = work;
            g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
            g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
            g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
    }
    count = g_Task->timer;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->unk_09 = count;
        g_Task->header.step += 1;
    }
}

/* func_801EF478 */
#include "overlays/bmagic/Effect_FinishTrail.h"

INCLUDE_ASM(func_801EF4E0);

INCLUDE_ASM(func_801EFA4C);

/* func_801F02A0 */
#include "overlays/bmagic/Effect_RecordTrail.h"

/* func_801F0390 */
#include "overlays/bmagic/Effect_ClearTrail.h"

MATCH void func_801F0478(void) {
    SYS_DISPATCH_BYTE(D_801F0A2C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F06D8();
    }
}

MATCH void func_801F04F0(void) {
    Battle_ProjectRange();
    g_Task->unk_30.half += 8;
    g_Task->unk_5D = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5E = (RANDOM_MASK(3)) + 1;
    g_Task->unk_5F = (RANDOM_MASK(3)) + 1;
    g_Task->unk_09 = 0;
    g_Task->timer  = 16;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801F05AC);

INCLUDE_ASM(func_801F0638);

/* The textured quad scratch: the corner radius and the colour channels, ahead of the quad corners. */
#define QUAD_RADIUS D_1F800000.view.effect.params[0]
#define QUAD_RED    D_1F800000.view.effect.params[5]
#define QUAD_GREEN  D_1F800000.view.effect.params[6]
#define QUAD_BLUE   D_1F800000.view.effect.params[7]

/* A 32x32 textured quad around the effect position, its corners twice the effect counter (byte 0x09) away,
 * coloured by the timer scaled per channel (bytes 0x5D-0x5F). */
MATCH void func_801F06D8(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim        = (POLY_FT4*)g_GfxPrimCursor;
    QUAD_RADIUS = g_Task->unk_09 * 2;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0 = g_Task->unk_2E.half + FIXED_MUL(rcos(ANGLE_45), QUAD_RADIUS);
    prim->y0 = g_Task->unk_30.half + FIXED_MUL(rsin(ANGLE_45), QUAD_RADIUS);
    prim->x1 = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), QUAD_RADIUS);
    prim->y1 = g_Task->unk_30.half + FIXED_MUL(rsin(1536), QUAD_RADIUS);
    prim->x2 = g_Task->unk_2E.half + FIXED_MUL(rcos(3584), QUAD_RADIUS);
    prim->y2 = g_Task->unk_30.half + FIXED_MUL(rsin(3584), QUAD_RADIUS);
    prim->x3 = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), QUAD_RADIUS);
    prim->y3 = g_Task->unk_30.half + FIXED_MUL(rsin(2560), QUAD_RADIUS);
    setTPage(prim, 0, 2, 832, 256);
    setClut(prim, 32, 506);
    prim->u0   = 128;
    prim->v0   = 32;
    prim->u1   = 160;
    prim->v1   = 32;
    prim->u2   = 128;
    prim->v2   = 64;
    prim->u3   = 160;
    prim->v3   = 64;
    QUAD_RED   = g_Task->timer * (s8)g_Task->unk_5D;
    QUAD_GREEN = g_Task->timer * (s8)g_Task->unk_5E;
    QUAD_BLUE  = g_Task->timer * (s8)g_Task->unk_5F;
    setRGB0(prim, QUAD_RED, QUAD_GREEN, QUAD_BLUE);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
