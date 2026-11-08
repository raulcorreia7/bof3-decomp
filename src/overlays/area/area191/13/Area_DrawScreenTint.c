#include "area191_13.h"

#include "shared/Area_DrawScreenTint.h"

MATCH void Area_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(0, 2, 960, 0) & HALF_MASK));
}
