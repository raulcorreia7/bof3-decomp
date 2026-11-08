#include "area172_13.h"

MATCH void func_801F2DF4(s32 arg0) {
    u16   tpage;
    TILE* tile;

    tpage = GetTPage(0, arg0 & 0xFF, 0x3C0, 0);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, 0xC);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    tile->r0 = g_Task->tint.bytes.unk_5D;
    tile->g0 = g_Task->tint.bytes.unk_5E;
    tile->b0 = g_Task->tint.bytes.unk_5F;
    tile->w  = 0x140;
    tile->x0 = 0;
    tile->y0 = 0;
    tile->h  = 0xF0;
    SetSemiTrans(tile, 1);
    SetShadeTex(tile, 0);
    GFX_AddPrim(5, 0x10);
}
