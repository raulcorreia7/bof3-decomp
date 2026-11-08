#include "area175_13.h"

#include "overlays/area/Screen_DrawTint.h"

MATCH void Screen_DrawTint(void) {
    Screen_DrawTintLayer(2U, getTPage(0, 2, 0x3C0, 0));
}
