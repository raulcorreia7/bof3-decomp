#include "engine/slus/slus.h"

/* Matching constraints of the shape: the || branch keeps GetGraphType()'s two
 * accepted modes on one shared draw-mode expression; the unsigned casts are
 * what make retail emit srl (not sra); the `tpage` local is what keeps the 0x2F
 * OR on the first operand (a single expression lets GCC reassociate it onto the
 * shifted term). */

/* builds the texture-page draw-mode word for the current graphics
 * mode: modes 1 and 2 take the shifted 0x300-bit form, every other mode the
 * 0x100/0x200-bit form, then the 12-byte primitive is appended at slot 1.
 */
MATCH void func_8014FC00(s32 mode) {
    s32 draw_mode;
    u32 tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        draw_mode = (((u32)(mode & 0x300) >> 3) | 0x8F);
    } else {
        tpage     = (((u32)(mode & 0x100)) >> 4) | 0x2F;
        draw_mode = (tpage | (((mode & 0x200)) << 2));
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, draw_mode, (RECT*)0);
    GFX_AddPrim(1, sizeof(DR_MODE));
}
