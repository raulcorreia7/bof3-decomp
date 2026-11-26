#include "area030_04.h"

/* The accessory slot list sits this far past the panel style byte. */
#define FISHING_ACCESSORY_SLOT_OFFSET 0x87A
/* The accessory slot list: one byte per slot, naming the accessory type. */
#define FISHING_ACCESSORY_SLOT_COUNT  128
/* Each accessory row is one icon cell tall. */
#define FISHING_ACCESSORY_ROW_HEIGHT  13

/* Draws the accessory slot list: two icon rows per accessory with
 * its quantity, then the footer and the selection cursor clamp. */
#ifdef NON_MATCHING
// clang-format off
NON_MATCHING void func_801D7EB0(x, y)
s16 x;
u16 y;
// clang-format on
{
    FishingState* work;
    u8*           buffer;
    u8*           slot_list;
    s16           icon_y;
    s32           row_offset;
    s32           row;
    s32           slot;
    u8            qty;
    u8*           style;

    style = (u8*)&g_WindowStyle;
    UI_WindowDraw(x, (y + 1) & HALF_MASK, 139, 158, UI_WINDOW_OPEN_ALL, *style);
    row        = 0;
    row_offset = 0;
    buffer     = g_UiTextFormatBuffer;
    slot_list  = style + FISHING_ACCESSORY_SLOT_OFFSET;
    /* the accessory rows step down from the panel's first icon row */
    icon_y     = y + 25;
    for (slot = 0; slot < FISHING_ACCESSORY_SLOT_COUNT; slot++, slot_list++) {
        if (g_Accessories[*slot_list].type != ITEM_TYPE_FISHING_ROD) {
            continue;
        }
        work = TASK(FishingState);
        if (work->pos_x == row) {
            work->motion.half.cursor = slot;
        }
        if (D_80145E94[0] == 2 && !(((work = TASK(FishingState))->counter_07) & 1) && work->pos_x == row) {
            UI_TextDraw(x + 5, (s16)icon_y, UI_TEXT_DIM, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*slot_list]);
            UI_TextDraw(x + 5, (s16)(y + 23 + row_offset), 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*slot_list]);
            qty = g_InventoryCounts[3][slot];
            if (qty >= 2) {
                TEXT_Format(buffer, D_801D0C14, qty);
                UI_TextDrawGlyphString(x + 104, (s16)(y + 29 + row_offset), UI_TEXT_DIM, buffer);
                UI_TextDrawGlyphString(x + 104, (s16)(y + 27 + row_offset), 0, buffer);
            }
        } else {
            UI_TextDraw(x + 5, (s16)icon_y, 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*slot_list]);
            qty = g_InventoryCounts[3][slot];
            if (qty >= 2) {
                TEXT_Format(buffer, D_801D0C14, qty);
                UI_TextDrawGlyphString(x + 104, (s16)(y + 29 + row_offset), 0, buffer);
            }
        }
        icon_y += FISHING_ACCESSORY_ROW_HEIGHT;
        row_offset += FISHING_ACCESSORY_ROW_HEIGHT;
        row += 1;
    }
    work             = TASK(FishingState);
    work->step_delta = row;
    if (work->pos_x >= row) {
        if (row == 0) {
            work->pos_x = 0;
        } else {
            work->pos_x = row - 1;
        }
    }
    func_801D90FC(x, y);
    func_801D8248(x + 128, y + 28, 114);
    UI_TextDraw(x + 58, y + 7, 0, 3, D_801E21CC);
}
#else
INCLUDE_ASM(func_801D7EB0);
#endif
