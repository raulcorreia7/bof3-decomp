#include "area077_14.h"

/* func_801F3198 */
MATCH void GFX_AddBlendDrawMode(u8 blend_mode) {
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, blend_mode, FONT_TPAGE_X, FONT_TPAGE_Y));
}
