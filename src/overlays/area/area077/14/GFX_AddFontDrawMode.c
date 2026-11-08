#include "area077_14.h"

/* func_801F3198 */

MATCH void GFX_AddFontDrawMode(u8 blend_mode) {
    GFX_AddDrawMode(GetTPage(0, blend_mode, FONT_TPAGE_X, FONT_TPAGE_Y));
}
