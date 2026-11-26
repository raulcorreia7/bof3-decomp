#include "boss012_16.h"

/* Draws a textured quad from the screen top down to the task; shade picks the texture row. */
MATCH void func_800C1CD8(s32 shade) {
    POLY_FT4* poly;
    s32       bottom;
    Actor*    task;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100));

    poly        = (POLY_FT4*)g_GfxPrimCursor;
    poly->tpage = GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 0x340, 0x100);
    setRGB0(poly, 0x80, 0x80, 0x80);
    task = SELF(PartyMember);
    setXY2(poly, task->unk_18 - 0x28, 0, task->unk_18 + 0x40, 0);
    poly->x2 = task->unk_18 - 0x28;
    bottom   = task->gravity - 0x3C;
    poly->y2 = task->unk_1C + bottom;
    poly->x3 = task->unk_18 + 0x40;
    poly->y3 = (task->unk_1C - 0x3C) + task->gravity;
    setUV4(poly, 0, shade, 0x68, shade, 0, shade, 0x68, shade);
    SetPolyFT4(poly);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
