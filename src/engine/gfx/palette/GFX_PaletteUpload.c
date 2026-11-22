#include "engine/slus/slus.h"

/* refreshes the stage palette to VRAM when the stage serial is set,
 * then clears the serial.
 */
MATCH void GFX_PaletteUpload(void) {
    RECT rect;

    setRECT(&rect, 0, STAGE_PALETTE_Y, AREA_PALETTE_COLORS, AREA_PALETTE_ROWS);
    if (g_GfxPalettePending != 0) {
        LoadImage(&rect, (u_long*)AREA_PALETTE_WORK);
        g_GfxPalettePending = 0;
    }
}
