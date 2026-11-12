#include "magic070_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28_2.h"

#include "overlays/bmagic/func_801EED38.h"

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(5);
}

#include "overlays/bmagic/func_801EF1A4.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/func_801EF33C.h"

#include "overlays/bmagic/func_801EF380.h"

#include "overlays/bmagic/Effect_LaunchSparkle.h"

#include "overlays/bmagic/func_801EF67C.h"

#include "overlays/bmagic/func_801EF72C.h"

#include "overlays/bmagic/func_801EF810.h"

#include "overlays/bmagic/func_801EFA44.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EFCDC(void) {
    POLY_G3* prim;
    s32      tpage;
    s32      angle;
    s32      i;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, sizeof(DR_MODE));

    i                  = 0;
    D_1F800000_HALF[2] = D_801F17B4->unk_06 + RANDOM_MASK(3);
    D_1F800000_HALF[0] = LOHU(D_801F17B4->unk_20);
    D_1F800000_HALF[1] = D_801F17B4->unk_22;
    D_1F800000_HALF[4] = D_801F015C[D_801F17B4->unk_04][D_801F17B4->unk_03][0] * D_801F17B4->timer_05;
    D_1F800000_HALF[5] = D_801F015C[D_801F17B4->unk_04][D_801F17B4->unk_03][1] * D_801F17B4->timer_05;
    D_1F800000_HALF[6] = D_801F015C[D_801F17B4->unk_04][D_801F17B4->unk_03][2] * D_801F17B4->timer_05;
    D_1F800000_HALF[7] = D_801F17B4->timer_05;

    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = LOHU(D_1F800000_HALF[0]);
        prim->y0 = LOHU(D_1F800000_HALF[1]);
        angle    = i << 9;
        prim->x1 = LOHU(D_1F800000_HALF[0]) + FIXED_MUL(rsin(angle), D_1F800000_HALF[2]);
        prim->y1 = LOHU(D_1F800000_HALF[1]) + FIXED_MUL(rcos(angle), D_1F800000_HALF[2]);
        i++;
        angle    = i << 9;
        prim->x2 = LOHU(D_1F800000_HALF[0]) + FIXED_MUL(rsin(angle), D_1F800000_HALF[2]);
        prim->y2 = LOHU(D_1F800000_HALF[1]) + FIXED_MUL(rcos(angle), D_1F800000_HALF[2]);
        setRGB0(prim, LOHU(D_1F800000_HALF[4]), LOHU(D_1F800000_HALF[5]), LOHU(D_1F800000_HALF[6]));
        setRGB1(prim, LOHU(D_1F800000_HALF[7]), LOHU(D_1F800000_HALF[7]), LOHU(D_1F800000_HALF[7]));
        setRGB2(prim, LOHU(D_1F800000_HALF[7]), LOHU(D_1F800000_HALF[7]), LOHU(D_1F800000_HALF[7]));
        Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}
#else
INCLUDE_ASM(func_801EFCDC);
#endif

#include "overlays/bmagic/func_801F0000.h"

#include "overlays/bmagic/func_801F006C.h"
