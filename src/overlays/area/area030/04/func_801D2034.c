#include "area030_04.h"

/* Queues the two AREA030 icon strip primitives for the selected mode. */
MATCH void func_801D2034(s16 strip_x, s16 strip_y, u8 icon_mode, s32 icon_count) {
    Fishing_SetDrawMode(0, icon_mode);
    Fishing_DrawSprite(23, icon_mode, strip_x, strip_y);
    Fishing_DrawSprite((u8)(icon_count + 0x17), icon_mode, (strip_x + 40), strip_y);
}
