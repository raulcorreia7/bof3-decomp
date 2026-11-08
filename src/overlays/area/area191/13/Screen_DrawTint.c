#include "area191_13.h"

#include "overlays/area/Screen_DrawTint.h"

SCREEN_TINT_BODY(Screen_DrawTint, 5U, (GetTPage(0, 2, 0x3C0, 0) & 0xFFFF));
