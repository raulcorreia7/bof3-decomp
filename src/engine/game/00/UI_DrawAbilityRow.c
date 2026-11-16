#include "game_00.h"

/* func_801AF930 */
MATCH void UI_DrawAbilityRow(s32 x, s32 y, u8 shade, u8 element, u8* name, u8 cost, u8 flags) {
    s32 y2;
    u8* buffer;
    s32 count;

    y2 = y + 2;
    func_801AEA80(x & HALF_MASK, y2 & HALF_MASK, s_ItemIconIds[element], flags);
    count = Game_ReadCommand(name) & BYTE_MASK;
    UI_DrawText((x + 10), y, shade, count, name);
    buffer = g_UiFormatBuffer;
    TEXT_Format(buffer, D_80195F98, cost);
    UI_DrawGlyphString((x + 109), y2, shade, buffer);
}
