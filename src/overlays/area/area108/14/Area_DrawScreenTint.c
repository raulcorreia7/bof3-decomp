#include "area108_14.h"

#include "shared/Area_DrawScreenTint.h"

MATCH void Area_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK));
}
