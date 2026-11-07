#include "game_00.h"

MATCH void func_801AF800(s16 record_x, s32 record_y, u8 record_kind, u8 record_mode, s32 record_index, s32 record_shade,
                         s32 sprite_flag) {
    s16   x;
    s32   row;
    u8    mode;
    u32   shade;
    u8    flag;
    u8*   entry;
    u8    index;
    u8    kind;
    u8    shade_byte;
    u8    table_index;
    char* buffer;
    u16   ux;

    index       = record_index;
    shade_byte  = record_shade;
    x           = record_x;
    mode        = record_mode;
    flag        = sprite_flag;
    kind        = record_kind;
    table_index = Item_GetKind(mode, index);
    row         = record_y + 2;
    ux          = x;
    func_801AEA80(ux, row & HALF_MASK, s_ItemSpriteIds[table_index], flag);
    entry = Item_GetRecord(mode, index);
    kind &= BYTE_MASK;
    UI_DrawText(x + 10, record_y, kind, func_801AF20C(entry) & BYTE_MASK, entry);
    shade = shade_byte & BYTE_MASK;
    if (shade >= 2U) {
        buffer = (char*)g_UiFormatBuffer;
        TEXT_Format(buffer, D_80195F90, shade);
        UI_DrawGlyphString((x + 109), row, kind, (const u8*)buffer);
    }
}
