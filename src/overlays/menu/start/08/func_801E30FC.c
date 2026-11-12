#include "start_08.h"

MATCH void func_801E30FC(u16 row_x, u16 row_y, s32 row_flags) {
    u8 data[24];
    /* FAKE: retail keeps the row y in s0. */
    FAKE_REG(u16, y, "s0");

    memcpy(data, s_RowCaptionTags, 0x18);
    y = row_y;
    if (row_flags & 0x20) {
        UI_DrawText(row_x + 6, y + 1, 2, 3, data);
    } else if (row_flags & 0x40) {
        UI_DrawText(row_x + 6, y + 1, 1, 3, (data + 3));
    } else if (row_flags & 0x10) {
        UI_DrawText(row_x + 6, y + 1, 6, 3, (data + 6));
    } else if (row_flags & 0x80) {
        UI_DrawText(row_x + 6, y + 1, 5, 3, (data + 9));
    } else if (row_flags & 0x4) {
        UI_DrawText(row_x + 4, y + 1, 0, 3, (data + 0xC));
        UI_DrawTextString(row_x + 12, y + 5, 0, 1, data + 0x12);
    } else if (row_flags & 0x8) {
        UI_DrawText(row_x + 4, y + 1, 0, 3, (data + 0xF));
        UI_DrawTextString(row_x + 12, y + 5, 0, 1, data + 0x12);
    } else if (row_flags & 0x100) {
        if (GetGraphType() != 1) {
            GetGraphType();
        }
        GFX_AddDrawMode(0xF);
        y = (y + 3) & HALF_MASK;
        Menu_DrawPanelIcon(row_x + 1, y, 6, 2, GetClut(0, STAGE_PALETTE_Y) & HALF_MASK, 128);
        Menu_DrawPanelIcon(row_x + 9, y, 7, 2, GetClut(0, STAGE_PALETTE_Y) & HALF_MASK, 128);
        Menu_DrawPanelIcon(row_x + 0x11, y, 8, 2, GetClut(0, STAGE_PALETTE_Y) & HALF_MASK, 128);
    }
}
