#include "area172_13.h"
#include "shared/Area_DrawScreenTint.h"

MATCH void func_801F2DF4(s32 abr) {
    Screen_DrawTintLayer(5, (GetTPage(0, (u8)abr, 960, 0) & HALF_MASK));
}
