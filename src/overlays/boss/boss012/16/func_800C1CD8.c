#include "boss012_16.h"
#include "area/spad.h"

#ifdef NON_MATCHING
NON_MATCHING void func_800C1CD8(s32 shade) {
    POLY_FT4* poly;
    s32       bottom;
    /* FAKE: retail keeps the task pointer in a0 while the poly copy moves into s0. */
    FAKE_REG(Actor*, task, "a0");

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100), 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    poly        = (POLY_FT4*)g_GfxPrimCursor;
    poly->tpage = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
    setRGB0(poly, 0x80, 0x80, 0x80);
    task     = g_Task;
    poly->x0 = task->unk_18 - 0x28;
    poly->y0 = 0;
    poly->x1 = task->unk_18 + 0x40;
    poly->y1 = 0;
    poly->x2 = task->unk_18 - 0x28;
    bottom   = task->gravity - 0x3C;
    poly->y2 = task->unk_1C + bottom;
    poly->x3 = task->unk_18 + 0x40;
    poly->y3 = (task->gravity - 0x3C) + task->unk_1C;
    setUV4(poly, 0, shade, 0x68, shade, 0, shade, 0x68, shade);
    SetPolyFT4(poly);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_800C1CD8);
#endif
