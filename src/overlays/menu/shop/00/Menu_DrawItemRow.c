#include "shop_00.h"

MATCH void Menu_DrawItemRow(s32 x0, s32 y0, s32 item, s32 selection) {
    u8* cell;
    s32 row_off;
    u8  count;
    u8  mode;
    u8  palette;
    u8  item_index;
    s16 tx;
    s16 stat_x;
    s16 stat_y;
    s32 count_y;

    mode       = selection & BYTE_MASK;
    palette    = (u8)((0u - (u32)(mode != 0)) & 7);
    item_index = item & BYTE_MASK;
    UI_DrawWindowOutline((s16)(x0 + 2), (s16)(y0 + 2), 0x86, 0x2A, 0xF1);
    row_off = item_index * 0xA4;
    cell    = (u8*)&g_Characters[0].max_hp + row_off;
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x4u));
    stat_x = (s16)(x0 + 0x29);
    stat_y = (s16)(y0 + 5);
    UI_DrawGlyphString(stat_x, stat_y, (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x6u));
    UI_DrawGlyphString(stat_x, (s16)(y0 + 18), (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0xAu));
    UI_DrawGlyphString((s16)(x0 + 111), stat_y, (u32)palette, g_UiFormatBuffer);
    sprintf((s8*)g_UiFormatBuffer, g_MenuStatFormat, FIELD(u16, cell, 0x8u));
    UI_DrawGlyphString((s16)(x0 + 111), (s16)(y0 + 18), (u32)palette, g_UiFormatBuffer);
    UI_DrawText((s16)(x0 + 5), (s16)(y0 + 3), (s32)palette, 4U, (u8*)(&D_801E5880));
    UI_DrawText((s16)(x0 + 5), (s16)(y0 + 16), (s32)palette, 4U, (&D_801E5880[6]));
    UI_DrawText((s16)(x0 + 75), (s16)(y0 + 3), (s32)palette, 4U, (&D_801E5880[0xC]));
    UI_DrawText((s16)(x0 + 75), (s16)(y0 + 16), (s32)palette, 4U, (&D_801E5880[0x12]));
    UI_DrawWindowOutline((s16)(x0 + 0x33), (s16)(y0 + 0x2E), 0x56, 0x14, 0xF1);
    Menu_DrawIcon((u16)(x0 + 0x36), (u16)(y0 + 0x30), 4U, mode);
    sprintf((s8*)g_UiFormatBuffer, g_MenuZennyFormat, *(s32*)((u8*)&g_Characters[0].exp + row_off));
    UI_DrawGlyphString((s16)(x0 + 78), (s16)(y0 + 48), (u32)palette, g_UiFormatBuffer);
    Menu_DrawIcon((u16)(x0 + 0x36), (u16)(y0 + 0x39), 5U, mode);
    count = ((u8*)&g_Characters[0].level)[row_off];
    if (count < 0x63U) {
        count_y = y0;
        sprintf((s8*)g_UiFormatBuffer, g_MenuZennyFormat, Char_GetExpForLevel(item_index, (count + 1) & BYTE_MASK));
    } else {
        count_y = y0;
        sprintf((s8*)g_UiFormatBuffer, &D_801D0D0C);
    }
    UI_DrawGlyphString((s16)(x0 + 78), (s16)(count_y + 57), (u32)palette, g_UiFormatBuffer);
}
