#include "area030_04.h"

/* Draws the AREA030 counter panel: formats the current sub-state
 * count into the shared UI character buffer and queues both text rows. */
MATCH void func_801D7B64(void) {
    FishingState* record;
    u8*           buffer;

    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(18, 1, 240, 66);
    UI_TextDrawAscii(284, 69, 0, D_801D0C10);

    buffer = g_UITextFormatBuffer;
    record = SELF(FishingState);
    TEXT_Format(buffer, D_801D0C04, record->bounce.half.key + 1);

    if (buffer[0] == ' ') {
        buffer[0] = STRING_SPACE;
    }

    UI_TextDraw(250, 69, 0, 2, buffer);
}
