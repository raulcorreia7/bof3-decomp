#include "area030_04.h"

/* Each item icon is one cell wide. */
#define FISHING_ICON_STRIDE     8
/* The item icons in a section, and the labelled column rows beside them. */
#define FISHING_ICON_ROW_COUNT  10
#define FISHING_LABEL_ROW_COUNT 16
/* The panel frame is this wide, and the labelled column sits this far right. */
#define FISHING_PANEL_WIDTH     0x8A
#define FISHING_LABEL_COLUMN_X  0x88

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
    palette = &g_SaveData.window_style;
    UI_DrawWindow(panel_x, ((y + 2)), FISHING_PANEL_WIDTH, 0x3A, 0x80, *palette);
    UI_DrawWindow(panel_x, ((y + 0x42)), FISHING_PANEL_WIDTH, 0x5C, 0x80, *palette);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, panel_x, panel_y);
    for (i = 0; i < FISHING_ICON_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + 0x20;
        func_801E0DCC(0x26, 1, (panel_x + offset), panel_y);
    }
    func_801E0DCC(0x27, 1, (panel_x + 0x70), panel_y);
    func_801E0DCC(0x28, 1, panel_x + FISHING_LABEL_COLUMN_X, panel_y);
    label_y = panel_y + 0x18;
    func_801D799C(panel_x, label_y, 0x1E, 0);
    func_801D799C(panel_x + FISHING_LABEL_COLUMN_X, label_y, 0x1E, 1);
    label_y = panel_y + 0x36;
    func_801E0DCC(0x3C, 1, panel_x, label_y);
    for (i = 0; i < FISHING_LABEL_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + FISHING_ICON_STRIDE;
        func_801E0DCC(0x3D, 1, (panel_x + offset), label_y);
    }
    func_801E0DCC(0x3E, 1, panel_x + FISHING_LABEL_COLUMN_X, (panel_y + 0x36));
    func_801E0DCC(0x25, 1, panel_x, panel_y + 0x40);
    for (i = 0; i < FISHING_ICON_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + 0x20;
        func_801E0DCC(0x26, 1, (panel_x + offset), panel_y + 0x40);
    }
    func_801E0DCC(0x27, 1, (panel_x + 0x70), panel_y + 0x40);
    func_801E0DCC(0x28, 1, panel_x + FISHING_LABEL_COLUMN_X, panel_y + 0x40);
    label_y = panel_y + 0x58;
    func_801D799C(panel_x, label_y, 0x40, 0);
    func_801D799C(panel_x + FISHING_LABEL_COLUMN_X, label_y, 0x40, 1);
    label_y = panel_y + 0x98;
    func_801E0DCC(0x3C, 1, panel_x, label_y);
    for (i = 0; i < FISHING_LABEL_ROW_COUNT; i++) {
        offset = (i * FISHING_ICON_STRIDE) + FISHING_ICON_STRIDE;
        func_801E0DCC(0x3D, 1, (panel_x + offset), label_y);
    }
    func_801E0DCC(0x3E, 1, panel_x + FISHING_LABEL_COLUMN_X, (panel_y + 0x98));
}
