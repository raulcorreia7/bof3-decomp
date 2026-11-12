#include "area030_04.h"

/* Draws the AREA030 icon cell at the given position and queues the
 * sprite selected by the palette index, unless the index is the null value. */
MATCH void Fishing_DrawIconRow(s16 cell_x, s16 cell_y, u16 icon_index) {
    Fishing_SetDrawMode(3, 1);
    Fishing_DrawSprite(12, 1, cell_x, cell_y);

    if (icon_index != 65535) {
        UI_DrawText((cell_x + 10), (cell_y + 8), 0, 0xFF, (u8*)(*(u16*)((u8*)MEM_PTR(const volatile u16, 0x80010000u) + icon_index * 2) + 0x80010000u));
    }
}
