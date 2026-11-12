#include "area172_13.h"

#include "shared/Area_DrawScreenTint.h"

MATCH void func_801F2DF4(s32 blend_mode) {
    Screen_DrawTintLayer(5, GetTPage(0, blend_mode & BYTE_MASK, 960, 0));
}
