#include "magic106_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEFAC */
#include "overlays/bmagic/shared/Effect_StartOrbit.h"

MATCH void func_801EF16C(void) {
    s32 threshold;

    g_BMagicOrbit->radius -= 2;
    g_BMagicOrbit->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos((s16)g_BMagicOrbit->angle) * g_BMagicOrbit->radius;
    g_BMagicOrbit->unk_0B++;
    if (g_BMagicOrbit->unk_09 < 16) {
        g_BMagicOrbit->unk_09 += 2;
    }
    threshold = ((g_BMagicOrbit->unk_04 >> 5) * 8) + 0x20;
    if (g_BMagicOrbit->radius <= threshold) {
        g_BMagicOrbit->header.step++;
        if (g_BMagicOrbit->unk_04 == 0) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
    }
}

/* func_801EF29C */
#include "overlays/bmagic/shared/Effect_StepOrbit.h"

MATCH void func_801EF418(void) {
    BMAGIC_ORBIT_BATTLER_AND_CLEAR(func_801EF970);
}

/* func_801EF52C */
#include "overlays/bmagic/shared/Effect_SetOrbitModelMatrix.h"

MATCH void func_801EF5F4(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    u8       i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[5] = g_BMagicOrbit->timer_05 * g_BMagicOrbit->unk_09;
    g_ScratchPad.cells.halves[6] = g_BMagicOrbit->timer_06 * g_BMagicOrbit->unk_09;
    g_ScratchPad.cells.halves[7] = g_BMagicOrbit->timer_07 * g_BMagicOrbit->unk_09;
    /* FAKE: retail stores vz and vy of the first corner through the scratch view, and only vx through g_ScratchPadVectors. */
    g_ScratchPad.vectors[0].vz   = 0;
    g_ScratchPad.vectors[0].vy   = 0;
    g_ScratchPadVectors[0].vx    = 0;
    for (i = 0; i < 4; i++) {
        g_ScratchPad.cells.halves[0] = D_801EF9D4[i];
        g_ScratchPad.cells.halves[1] = D_801EF9DC[i];
        g_ScratchPad.cells.halves[2] = D_801EF9E4[i];
        g_ScratchPad.cells.halves[3] = D_801EF9EC[i];
        g_ScratchPad.cells.halves[4] = ((g_BMagicOrbit->unk_0B + D_801EF9F4[i]) & 0xF) << 8;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]),
                  g_ScratchPadVectors[1].vz = (u32)rsin(g_ScratchPad.cells.halves[4]) >> 7);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        Area_CellAddPrim(g_BMagicOrbit->pos.x.fixed, g_BMagicOrbit->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH u32 func_801EF914(void) {
    u8 index;

    for (index = 0u; index < 96; index++) {
        if ((D_801EF9F8[index << 5] & 0x1) == 0) {
            D_801EF9F8[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801EF970(void) {
    g_BMagicOrbit->header.flags = 0;
    g_BMagicOrbit->header.mode  = 0;
    g_BMagicOrbit->header.step  = 0;
    g_BMagicOrbit->unk_03       = 0;
    g_BMagicOrbit->unk_04       = 0;
}
