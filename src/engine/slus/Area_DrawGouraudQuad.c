#include "engine/slus/slus.h"

/* draws a Gouraud-shaded quadrangle sized and coloured from the
 * record at record when its corners fall inside the current draw area.
 */
MATCH void Area_DrawGouraudQuad(u32* record) {
    u8*      src;
    u32      x_limit;
    u32      y_limit;
    u32      packed;
    s32      tpage;
    POLY_G4* primitive;

    src = (u8*)record;
    if (D_8014933A != 0) {
        src += 4;
        x_limit = (u32)(0x7FFF - D_80149310) >> 8;
        y_limit = (u32)(0x8000 - D_80149314) >> 8;
        packed  = *(u32*)src;
        if (((s32)x_limit >= (s32)(packed & BYTE_MASK)) && ((s32)y_limit >= (s32)((packed >> 8) & BYTE_MASK)) &&
            ((s32)((packed >> 16) & BYTE_MASK) >= (s32)x_limit) && ((s32)(packed >> 24) >= (s32)y_limit)) {
            if (GetGraphType() == 1) {
                tpage = 0x225;
            } else if (GetGraphType() == 2) {
                tpage = 0x225;
            } else {
                tpage = 0x95;
            }
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, NULL);
            GFX_AddPrim(7, 0xC);
            primitive = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(primitive);
            SetSemiTrans(primitive, 0);
            setXY4(primitive, 0, 0, 320, 0, 0, 240, 320, 240);
            if (D_8014933C != 0) {
                src += 8;
            } else {
                src += 4;
            }
            setRGB0(primitive, primitive->r1 = (*(u32*)src & 0x1F) * 8, primitive->g1 = (*(u32*)src >> 2) & 0xF8,
                    primitive->b1 = (*(u32*)src >> 7) & 0xF8);
            setRGB2(primitive, primitive->r3 = (*(u16*)(src + 2) & 0x1F) * 8, primitive->g3 = (*(u32*)src >> 18) & 0xF8,
                    primitive->b3 = (*(u32*)src >> 23) & 0xF8);
            GFX_AddPrim(7, 0x24);
        }
    }
}
