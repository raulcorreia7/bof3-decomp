#include "area030_04.h"

/* Each item icon is one cell wide. */
#define FISHING_ICON_STRIDE     8
/* The item icons in a section, and the labelled column rows beside them. */
#define FISHING_ICON_ROW_COUNT  10
#define FISHING_LABEL_ROW_COUNT 16
/* The panel frame is this wide, and the labelled column sits this far right. */
#define FISHING_PANEL_WIDTH     138
#define FISHING_LABEL_COLUMN_X  136

/* Draws the two-line AREA030 panel: a 0x8A-wide frame per section,
 * the item icon rows, and the two labelled columns. */
MATCH void func_801D8D70(u16 x, u16 y) {
    u16 panel_x;
    u16 panel_y;
    u8* palette;
    s16 label_y;
    s32 i;
    s32 offset;

    panel_x = x;
    panel_y = y;
    palette = &g_WindowStyle;
    UI_DrawWindow(panel_x, ((y + 2)), FISHING_PANEL_WIDTH, 58, 0x80, *palette);
    UI_DrawWindow(panel_x, ((y + 66)), FISHING_PANEL_WIDTH, 92, 0x80, *palette);
    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(37, 1, panel_x, panel_y);
    for (i = 0; i < FISHING_ICON_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + 32;
        Fishing_DrawSprite(38, 1, (panel_x + offset), panel_y);
    }
    Fishing_DrawSprite(39, 1, (panel_x + 112), panel_y);
    Fishing_DrawSprite(40, 1, panel_x + FISHING_LABEL_COLUMN_X, panel_y);
    label_y = panel_y + 24;
    Fishing_DrawWindowFill(panel_x, label_y, 30, 0);
    Fishing_DrawWindowFill(panel_x + FISHING_LABEL_COLUMN_X, label_y, 30, 1);
    label_y = panel_y + 54;
    Fishing_DrawSprite(60, 1, panel_x, label_y);
    for (i = 0; i < FISHING_LABEL_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + FISHING_ICON_STRIDE;
        Fishing_DrawSprite(61, 1, (panel_x + offset), label_y);
    }
    Fishing_DrawSprite(62, 1, panel_x + FISHING_LABEL_COLUMN_X, (panel_y + 54));
    Fishing_DrawSprite(37, 1, panel_x, panel_y + 64);
    for (i = 0; i < FISHING_ICON_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + 32;
        Fishing_DrawSprite(38, 1, (panel_x + offset), panel_y + 64);
    }
    Fishing_DrawSprite(39, 1, (panel_x + 112), panel_y + 64);
    Fishing_DrawSprite(40, 1, panel_x + FISHING_LABEL_COLUMN_X, panel_y + 64);
    label_y = panel_y + 88;
    Fishing_DrawWindowFill(panel_x, label_y, 64, 0);
    Fishing_DrawWindowFill(panel_x + FISHING_LABEL_COLUMN_X, label_y, 64, 1);
    label_y = panel_y + 152;
    Fishing_DrawSprite(60, 1, panel_x, label_y);
    for (i = 0; i < FISHING_LABEL_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + FISHING_ICON_STRIDE;
        Fishing_DrawSprite(61, 1, (panel_x + offset), label_y);
    }
    Fishing_DrawSprite(62, 1, panel_x + FISHING_LABEL_COLUMN_X, (panel_y + 152));
}
