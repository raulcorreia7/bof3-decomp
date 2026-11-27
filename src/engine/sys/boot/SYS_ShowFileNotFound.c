#include "engine/slus/slus.h"

/* draws the missing-file notice and the three scratchpad ID bytes,
 * yields one scheduler tick, and repeats forever.
 */
MATCH void SYS_ShowFileNotFound(void) {
    while (1) {
        UI_TextDrawGlyphString(160, 100, 0, (const u8*)D_80149F9C);
        TEXT_Format(g_UITextFormatBuffer, D_80149FAC, g_ScratchPad.cells.bytes[0], g_ScratchPad.cells.bytes[1], g_ScratchPad.cells.bytes[2]);
        UI_TextDrawGlyphString(160, 116, 0, (const u8*)g_UITextFormatBuffer);
        SYS_ThreadWait(1);
    }
}
