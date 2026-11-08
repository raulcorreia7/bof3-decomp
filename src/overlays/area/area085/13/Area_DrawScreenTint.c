#include "area085_13.h"

#include "shared/Area_DrawScreenTint.h"

MATCH void Area_DrawScreenTint(void) {
    Screen_DrawTintLayer(5, getTPage(0, 2, 960, 0));
}
