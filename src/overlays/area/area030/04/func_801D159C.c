#include "area030_04.h"

/* Draws the AREA030 countdown panel: it lays out three icon cells,
 * formats the remaining count from the world byte pair into the shared UI
 * character buffer, and draws the two-line caption with an extra emphasis row
 * when the count has reached 50 in graphics mode 4. */
MATCH void func_801D159C(s16 panel_x, s16 panel_y) {
    s8 value;

    func_801E0C80(5, 3);
    func_801E0DCC(0xD, 3, (panel_x + 0x18), (panel_y + 8));
    func_801E0C80(0, 3);
    func_801E0DCC(0xE, 3, panel_x, panel_y);
    func_801E0DCC(0xF, 3, (panel_x + 0x100), panel_y);

    if (g_ActorSlots[0].mode == 0) {
        value = 0;
    } else {
        /* FAKE: retail reads the low byte of the y integer half (lbu). */
        value = 0x3E - *(u8*)&g_ActorSlots[0].y.part.integer;
    }

    CLAMP_MIN(value, 0);
    sprintf((char*)g_UiFormatBuffer, (const char*)D_801D0C04, value);

    if (value >= 0x32 && D_80145E92[0] == 4 && (g_FrameCount & 4) != 0) {
        UI_DrawAsciiString((panel_x + 0xF0), (panel_y + 0x1A), 2, g_UiFormatBuffer);
    } else {
        UI_DrawAsciiString((panel_x + 0xF0), (panel_y + 0x1A), 0, g_UiFormatBuffer);
    }
    func_801D195C(panel_x, panel_y);
}
