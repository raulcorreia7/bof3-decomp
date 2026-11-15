#include "engine/slus/slus.h"

/* draws the missing-file notice and the three scratchpad ID bytes,
 * yields one scheduler tick, and repeats forever.
 */
MATCH void SYS_ShowFileNotFound(void) {
    while (1) {
        UI_DrawGlyphString(160, 100, 0, (const u8*)D_80149F9C);
        TEXT_Format(g_UiFormatBuffer, D_80149FAC, D_1F800000[0], D_1F800000[1], D_1F800000[2]);
        UI_DrawGlyphString(160, 116, 0, (const u8*)g_UiFormatBuffer);
        SYS_ThreadWait(1);
    }
}
