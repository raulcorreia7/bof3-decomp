#include "area030_04.h"

/* PsyQ SetSprt16; the SDK map omits this entry, so the address name is kept. */

/* Configures the shared 16x16 sprite primitive as the AREA030 mode
 * icon and appends it with the caller's semi-transparency mode. The sprite's U
 * coordinate comes from the texture table entry selected by the world graphics
 * mode bits. */
MATCH void func_801D1818(s16 sprite_x, s16 sprite_y, u8 icon_index) {
    SPRT_16* primitive;

    func_801E0C80(0, icon_index);
    primitive = (SPRT_16*)g_GfxPrimCursor;
    SetSprt16(primitive);
    setRGB0(primitive, 128, 128, 128);
    primitive->clut = 0x7A40;
    setXY0(primitive, sprite_x, sprite_y);
    setUV0(primitive, D_801E1D0C[(g_FrameCount >> 3) & 3], 72);
    GFX_AddPrim(icon_index, 0x10);
}
