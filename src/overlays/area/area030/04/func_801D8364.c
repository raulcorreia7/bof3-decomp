#include "area030_04.h"

/* Draws the area-030 accessory rows: the accessory icons of every
 * slot with their count text and the frame behind them. */
/* RESIDUAL: same size as retail; the loop pass moves panel_x + 104 out of the row loop, where
 * retail rebuilds it at each count text. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8364(s16 panel_x, s16 panel_y) {
    s16 x;
    s16 base_y;
    s16 bar_y;
    s16 row_offset;
    s32 shadow_y;
    s32 slot;
    s32 row;
    s32 index;
    s32 height;
    u8  offset_y;
    u8  y_offset;
    u8  max_count;
    u8  max_rows;
    u8  accessory;
    u8* cursor;
    u8* text;

    UI_WindowDraw(panel_x, panel_y + 1, 139, 158, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);
    if (TASK(FishingState)->step_index != 0) {
        TASK(FishingState)->step_index--;
        if (TASK(FishingState)->counter_08 != 0) {
            max_rows = TASK(FishingState)->y_38.slot.low.unk_38;
        } else {
            max_rows = TASK(FishingState)->y_38.slot.low.unk_38 - 1;
        }
        max_count = 10;
        if (TASK(FishingState)->counter_08 != 0) {
            offset_y = 25 - TASK(FishingState)->step_index * 4;
        } else {
            offset_y = 25 - (3 - TASK(FishingState)->step_index) * 4;
        }
    } else {
        max_rows  = TASK(FishingState)->y_38.slot.low.unk_38;
        max_count = 9;
        offset_y  = 25;
    }
    slot       = 0;
    row        = 0;
    index      = 0;
    text       = g_UiTextFormatBuffer;
    cursor     = g_InventoryIds[3];
    x          = panel_x + 5;
    row_offset = 0;
    base_y     = panel_y + offset_y;
    bar_y      = base_y;
    shadow_y   = -2;
    do {
        accessory = *cursor;
        if (g_Accessories[accessory].type == ITEM_TYPE_FISHING_LURE) {
            if (row >= max_rows && index < max_count) {
                if (*D_80145E94 == 2 && (TASK(FishingState)->counter_07 & 1) && TASK(FishingState)->cursor_10 == index) {
                    UI_TextDraw(x, bar_y, UI_TEXT_DIM, ITEM_NAME_LENGTH, (u8*)&g_Accessories[accessory]);
                    UI_TextDraw(x, base_y + shadow_y, 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*cursor]);
                    if (g_InventoryCounts[3][slot] >= 2) {
                        TEXT_Format(text, D_801D0C14, g_InventoryCounts[3][slot]);
                        UI_TextDrawGlyphString(panel_x + 104, base_y + (row_offset + 4), UI_TEXT_DIM, text);
                        UI_TextDrawGlyphString(panel_x + 104, base_y + (row_offset + 2), 0, text);
                    }
                } else {
                    UI_TextDraw(x, bar_y, 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*cursor]);
                    if (g_InventoryCounts[3][slot] >= 2) {
                        TEXT_Format(text, D_801D0C14, g_InventoryCounts[3][slot]);
                        UI_TextDrawGlyphString(panel_x + 104, base_y + (row_offset + 4), 0, text);
                    }
                }
                if (TASK(FishingState)->cursor_10 == index) {
                    TASK(FishingState)->y_38.slot.slot = slot;
                }
                bar_y += 13;
                row_offset += 13;
                shadow_y += 13;
                index++;
            }
            row++;
        }
        slot++;
        cursor++;
    } while (slot < 128);
    TASK(FishingState)->unk_1C = row - 1;
    if (TASK(FishingState)->cursor_10 >= index) {
        if (row - 1 != 0 && index != 0) {
            TASK(FishingState)->cursor_10 = index - 1;
        } else {
            TASK(FishingState)->cursor_10 = 0;
        }
    }
    func_801D90FC(panel_x, panel_y);
    slot  = 0;
    index = 0;
    do {
        if (g_Accessories[g_InventoryIds[3][slot]].type == ITEM_TYPE_FISHING_LURE) {
            index++;
        }
        slot++;
    } while (slot < 128);
    if (index < 10) {
        height   = 114;
        y_offset = 28;
    } else {
        index -= 9;
        height   = 114 - index * 6;
        y_offset = TASK(FishingState)->y_38.slot.low.pos_low * 6 + 28;
        if (TASK(FishingState)->step_index != 0) {
            if (TASK(FishingState)->counter_08 != 0) {
                y_offset += TASK(FishingState)->step_index * 2;
            } else {
                y_offset -= TASK(FishingState)->step_index * 2;
            }
        }
    }
    func_801D8248(panel_x + 128, panel_y + y_offset, height & 0xFE);
    UI_TextDraw(panel_x + 55, panel_y + 7, 0, 4, (u8*)&D_801E21D0);
}
#else
INCLUDE_ASM(func_801D8364);
#endif
