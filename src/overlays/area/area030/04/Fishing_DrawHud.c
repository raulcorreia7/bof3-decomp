#include "area030_04.h"

/* Draws the AREA030 countdown panel: it lays out three icon cells,
 * formats the remaining count from the world byte pair into the shared UI
 * character buffer, and draws the two-line caption with an extra emphasis row
 * when the count has reached 50 in graphics mode 4. */
/* func_801D159C */
MATCH void Fishing_DrawHud(s16 panel_x, s16 panel_y) {
    s8 value;

    Fishing_SetDrawMode(5, 3);
    Fishing_DrawSprite(13, 3, (panel_x + 24), (panel_y + 8));
    Fishing_SetDrawMode(0, 3);
    Fishing_DrawSprite(14, 3, panel_x, panel_y);
    Fishing_DrawSprite(15, 3, (panel_x + 256), panel_y);

    if (g_ActorSlots[0].header.mode == 0) {
        value = 0;
    } else {
        /* FAKE: retail reads the low byte of the y integer half (lbu). */
        value = 62 - *(u8*)&COORD_INT(g_ActorSlots[0].pos.y);
    }

    CLAMP_MIN(value, 0);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, value);

    if (value >= 0x32 && D_80145E92[0] == 0x4 && (g_FrameCount & 4) != 0) {
        UI_DrawAsciiString((panel_x + 240), (panel_y + 26), 2, g_UiFormatBuffer);
    } else {
        UI_DrawAsciiString((panel_x + 240), (panel_y + 26), 0, g_UiFormatBuffer);
    }
    Fishing_DrawDepthGauge(panel_x, panel_y);
}
