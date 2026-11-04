#include "engine/slus/slus.h"

/* refreshes the stage palette to VRAM when the stage serial is set,
 * then clears the serial.
 */
MATCH void GFX_UploadPalette(void) {
    RECT rect;

    rect.x = 0;
    rect.y = 480;
    rect.w = 256;
    rect.h = 32;
    if (g_GfxPalettePending != 0) {
        LoadImage(&rect, (u_long*)AREA_PALETTE_WORK);
        g_GfxPalettePending = 0;
    }
}
