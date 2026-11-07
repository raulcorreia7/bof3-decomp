#include "area030_04.h"

/* Draws the AREA030 counter panel: formats the current sub-state
 * count into the shared UI character buffer and queues both text rows. */
MATCH void func_801D7B64(void) {
    FishingState* record;
    u8*           buffer;

    func_801E0C80(0, 1);
    func_801E0DCC(0x12, 1, 0xF0, 0x42);
    UI_DrawAsciiString(0x11C, 0x45, 0, D_801D0C10);

    buffer = g_UiFormatBuffer;
    record = FISHING_STATE;
    TEXT_Format(buffer, D_801D0C04, record->bounce_3C.half.key_3E + 1);

    if (buffer[0] == ' ') {
        buffer[0] = STRING_SPACE;
    }

    UI_DrawText(0xFA, 0x45, 0, 2, buffer);
}
