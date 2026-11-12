#include "area033_13.h"

MATCH void func_801F3FF8(s16 x, s16 y) {
    if ((g_AreaDrawFlags & (AREA_DRAW_SORTED_RECORDS | 0x2 | AREA_DRAW_APPEND_ACTOR_PRIMITIVES | AREA_DRAW_APPEND_AREA_PRIMITIVES)) == 0) {
        return;
    }
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x, y, 4);
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x + 0x80, y, 5);
    UI_DrawText(x + 4, y + 4, 0, 0xFF, (u8*)(D_80010008 + 0x80010000u));
}
