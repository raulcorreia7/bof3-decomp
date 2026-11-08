#include "area149_13.h"

#include "overlays/area/Screen_DrawTint.h"

MATCH void Screen_DrawTint(void) {
    Screen_DrawTintLayer(5U, (GetTPage(0, 2, 0x3C0, 0) & 0xFFFF));
}
