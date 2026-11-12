#include "magic097_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC8(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), g_Task->header.step);
    func_800AF764();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 32, 0x7);
        g_Task->param.unk_0B += 4;
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 64, 0xF);
        Effect_DrawBolt();
        g_Task->param.unk_0B += 4;
        func_801EF5C4(MAGIC097_BAND_HEIGHT, 96, 0x1F);
        Effect_DrawBolt();
        g_Task->param.unk_0B -= 8;
        g_Task->unk_2E.half += 16;
        func_801F083C();
        g_Task->unk_2E.half -= 32;
        func_801F083C();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownAndPickRandom.h"

INCLUDE_ASM(func_801EF1A4);

/* func_801EF324 */
#include "overlays/bmagic/Effect_ReleaseTarget.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF5C4);

INCLUDE_ASM(func_801EFE04);

/* Draws the lightning bolt of the effect as LINE_G2 segments: each segment swings by the effect ticker, its length
 * and brightness flicker at random, and it goes into the depth cell of the effect's position. The halfword copy of
 * Effect_DrawBolt.h. */
MATCH void Effect_DrawBolt(void) {
    LINE_G2* primitive;
    s16*     d;
    s16*     cell;
    s16*     vec;
    s16*     point;
    long     p;
    long     flag;
    s32      x;
    s32      y;
    u8       page;
    s32      i;

    d          = D_1F800000_HALF;
    vec        = D_1F800014_HALF;
    d[0]       = 0x40;
    D_1F800002 = ((g_Task->param.unk_0B + 2) & 0xF) << 8;
    D_1F800008 = g_Task->timer;
    i          = 1;
    D_1F800004 = RANDOM_MASK(0x3F);
    vec[0]     = 0;
    D_1F800016 = FIXED_MUL(rsin(D_1F800002), d[0]);
    D_1F800018 = 0;
    if (i < D_1F800008) {
        point = vec;
        cell  = d + 1;
        do {
            x = (point[0] >> 3) + g_Task->pos.x.fixed;
            y = (point[1] >> 3) + g_Task->pos.y.fixed;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(1, 1, 320, 256), 0);
            Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            SetSemiTrans(primitive, 1);
            RotTransPers(D_1F800014, (long*)&primitive->x0, &p, &flag);
            if RANDOM_MASK (1) {
                D_1F800000_HALF[0] = RANDOM_MASK(0x1F) + 0x40;
            } else {
                D_1F800000_HALF[0] = 0x40 - RANDOM_MASK(0x1F);
            }
            page     = (g_Task->param.unk_0B + i + 2) & 0xF;
            point[0] = 0;
            cell[0]  = page << 8;
            point[1] = FIXED_MUL(rsin(page << 8), cell[-1]);
            point[2] = -(i << 6);
            RotTransPers((SVECTOR*)point, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1] = (rand() + 0x40) & 0x3F;
            setRGB1(primitive, cell[1], cell[1], 32);
            Area_AddCellPrim(x, y, 2, sizeof(LINE_G2));
            i++;
        } while (i < cell[3]);
    }
}

INCLUDE_ASM(func_801F083C);
