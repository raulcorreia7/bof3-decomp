#include "batl_end_00.h"

MATCH void func_801F0A74(s16 x, s16 y, u8 clut, u8 category, u8 item, u8 amount, u8 shade) {
    u8* record;

    if (item == 0) {
        return;
    }
    if (amount == 0) {
        return;
    }
    func_801AEA80((u16)x, (u16)(y + 2), D_801F0CD4[Item_GetIcon(category, item) & BYTE_MASK], shade);
    record = Item_GetRecord(category, item);
    UI_DrawText(x + 10, y, clut, Game_ReadCommand(record) & BYTE_MASK, record);
    if (amount < 2) {
        return;
    }
    TEXT_Format(g_UiFormatBuffer, D_801EEC50, amount);
    UI_DrawGlyphString(x + 109, y + 2, clut, g_UiFormatBuffer);
}
