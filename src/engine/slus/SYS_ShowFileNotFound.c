#include "engine/slus/slus.h"

/* draws the missing-file notice and the three scratchpad ID bytes,
 * yields one scheduler tick, and repeats forever.
 */
MATCH void SYS_ShowFileNotFound(void) {
    while (1) {
        UI_DrawGlyphString(160, 100, 0, (const u8*)g_SysFileNotFoundText);
        TEXT_Format(g_UiFormatBuffer, g_SysFileNotFoundFormat, g_ScratchPad.cells.bytes[0], g_ScratchPad.cells.bytes[1], g_ScratchPad.cells.bytes[2]);
        UI_DrawGlyphString(160, 116, 0, (const u8*)g_UiFormatBuffer);
        SYS_ThreadWait(1);
    }
}
