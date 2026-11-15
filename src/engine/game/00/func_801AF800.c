#include "game_00.h"

MATCH void func_801AF800(s16 record_x, s32 record_y, u8 text_shade, u8 category, s32 item_id, s32 quantity, s32 sprite_flag) {
    s16   x;
    s32   row;
    u8    item_category;
    u32   count;
    u8    flag;
    u8*   entry;
    u8    item_id_byte;
    u8    text_color;
    u8    quantity_byte;
    u8    icon;
    char* buffer;
    u16   ux;

    item_id_byte  = item_id;
    quantity_byte = quantity;
    x             = record_x;
    item_category = category;
    flag          = sprite_flag;
    text_color    = text_shade;
    icon          = Item_GetIcon(item_category, item_id_byte);
    row           = record_y + 2;
    ux            = x;
    func_801AEA80(ux, row & HALF_MASK, s_ItemSpriteIds[icon], flag);
    entry = Item_GetRecord(item_category, item_id_byte);
    text_color &= BYTE_MASK;
    UI_DrawText(x + 10, record_y, text_color, Game_ReadCommand(entry) & BYTE_MASK, entry);
    count = quantity_byte & BYTE_MASK;
    if (count >= 2U) {
        buffer = (char*)g_UiFormatBuffer;
        TEXT_Format(buffer, D_80195F90, count);
        UI_DrawGlyphString((x + 109), row, text_color, (const u8*)buffer);
    }
}
