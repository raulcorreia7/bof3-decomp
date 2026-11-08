#include "area085_13.h"

#include "shared/Screen_DrawTint.h"

MATCH void Screen_DrawTint(void) {
    Screen_DrawTintLayer(5, getTPage(0, 2, 960, 0));
}
