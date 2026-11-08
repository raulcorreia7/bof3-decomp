#include "area149_13.h"

#include "shared/Screen_DrawTint.h"

MATCH void Screen_DrawTint(void) {
    Screen_DrawTintLayer(5, (GetTPage(0, 2, 960, 0) & 0xFFFF));
}
