#include "engine/slus/slus.h"

/* copies the four vertex pairs of the g_AreaCellPrims rows that the mask bits select (1, 2, 4. */
MATCH void Area_DrawCellQuad(s32 mask, s32 index) {
    POLY_F4*  primitive;
    u16*      color;
    POLY_FT4* record;
    s32       bit;

    for (bit = 1; bit < 8; bit <<= 1) {
        if (!(mask & bit)) {
            continue;
        }
        primitive = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(primitive);
        switch (bit) {
            case 1:
                record = &g_AreaCellPrims[index][g_FrameBufferIndex];
                break;
            case 2:
                record = &g_AreaCellPrims[g_AreaCellPrims[index][1].pad2][g_FrameBufferIndex];
                break;
            default:
                record = &g_AreaCellPrims[g_AreaCellPrims[index][1].pad1][g_FrameBufferIndex];
                break;
        }
        *(u32*)&primitive->x0 = *(u32*)&record->x0;
        *(u32*)&primitive->x1 = *(u32*)&record->x1;
        *(u32*)&primitive->x2 = *(u32*)&record->x2;
        *(u32*)&primitive->x3 = *(u32*)&record->x3;
        /* FAKE: the constant address form keeps the retail base materialization (the symbol form changes it). */
        color                 = ((AreaMapBundle*)MAP_BUNDLE_BASE)->color_1A + (mask >> 3);
        setRGB0(primitive, ((*color & 0x1F) * 8), ((*color >> 2) & 0xF8), ((*color >> 7) & 0xF8));
        GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_F4));
    }
}
