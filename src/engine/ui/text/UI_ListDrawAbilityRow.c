#include "engine/game/00/game_00.h"

/* func_801AF930 */
MATCH void UI_ListDrawAbilityRow(s32 x, s32 y, u8 shade, u8 element, u8* name, u8 cost, u8 flags) {
    s32 y2;
    u8* buffer;
    s32 count;

    y2 = y + 2;
    UI_IconDraw(x & HALF_MASK, y2 & HALF_MASK, s_ItemIconIds[element], flags);
    count = Game_ReadCommand(name) & BYTE_MASK;
    UI_TextDraw((x + 10), y, shade, count, name);
    buffer = g_UITextFormatBuffer;
    TEXT_Format(buffer, g_UIListAbilityRowFormat, cost);
    UI_TextDrawGlyphString((x + 109), y2, shade, buffer);
}
