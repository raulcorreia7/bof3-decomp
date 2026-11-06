#include "game_00.h"

MATCH void func_801AF930(s32 x, s32 y, u8 palette_index, u8 icon_index, u8* command_stream, u8 stat_value,
                         u8 sprite_flag) {
    s32 y2;
    u8* buffer;
    s32 count;

    y2 = y + 2;
    func_801AEA80(x & 0xFFFF, y2 & 0xFFFF, s_ItemIconIds[icon_index], sprite_flag);
    count = func_801AF20C(command_stream) & 0xFF;
    UI_DrawText((x + 10), y, palette_index, count, command_stream);
    buffer = g_UiFormatBuffer;
    sprintf((char*)buffer, (const char*)D_80195F98, stat_value);
    UI_DrawGlyphString((x + 109), y2, palette_index, buffer);
}
