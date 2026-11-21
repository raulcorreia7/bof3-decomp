#include "area098_13.h"

#include "shared/GFX_DrawProjectedDisc.h"

MATCH void func_801F4BC0(FallingSpark* slot) {
    GFX_DRAW_PROJECTED_DISC(&slot->x, slot->fade, 0x18, 2);
}
