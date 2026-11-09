#include "engine/slus/slus.h"

/* draws one flat-coloured line into the current primitive: sets the
 * rgb byte, writes both corner points, then appends the 0x10-byte primitive to
 * ordering table 1.
 */
/* func_8015A2B0 */
MATCH void UI_DrawLine(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u8 gray) {
    LINE_F2* primitive;
    u8       color;
    s16      x0;
    s16      y0;
    s16      x1;
    s16      y1;

    primitive = (LINE_F2*)g_GfxPrimCursor;
    color     = gray;
    x0        = start_x;
    y0        = start_y;
    x1        = end_x;
    y1        = end_y;
    SetLineF2(primitive);
    setRGB0(primitive, color, color, color);
    setXY2(primitive, x0, y0, x1, y1);
    GFX_AddPrim(1u, sizeof(LINE_F2));
}
