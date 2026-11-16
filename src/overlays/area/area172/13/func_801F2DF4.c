#include "area172_13.h"

#include "shared/Area_DrawScreenTint.h"

MATCH void func_801F2DF4(s32 blend_mode) {
    Screen_DrawTintLayer(5, GetTPage(TPAGE_DEPTH_4BIT, blend_mode & BYTE_MASK, FONT_TPAGE_X, FONT_TPAGE_Y));
}
