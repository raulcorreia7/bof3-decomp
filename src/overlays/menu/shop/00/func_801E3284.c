#include "shop_00.h"

MATCH void func_801E3284(MenuPanelTask* task) {
    u8* row;
    u8* icon;
    u8  group;
    u8  key;
    u8  index;
    s32 price;
    u8* text;

    row   = (u8*)task->item_table + task->unk_0B * 2;
    group = row[1];
    key   = row[2];

    price = Shop_ApplyPercent(Item_GetPrice(group, key) & HALF_MASK, task->unk_0A);
    icon  = Item_GetRecord(group, key);

    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, 170, 60, 0, g_WindowStyle);
    func_801AEA80((task->pos.x + 4) & HALF_MASK, (task->pos.y + 7) & HALF_MASK,
                  D_801E5E1C[Item_GetKind(group, key) & BYTE_MASK], 0);
    UI_DrawText((task->pos.x + 14), (task->pos.y + 4), 0, func_801AF20C(icon) & BYTE_MASK, icon);

    text = g_UiFormatBuffer;
    sprintf((char*)text, D_801D0E90, price * task->unk_0C);
    UI_DrawGlyphString((task->pos.x + 105), (task->pos.y + 18), 0U, text);

    sprintf((char*)text, D_801D0E98, task->unk_0C);
    UI_DrawGlyphString((task->pos.x + 137), (task->pos.y + 7), 0U, text);
    UI_DrawText((task->pos.x + 14), (task->pos.y + 32), 0, 0xFFU, Resource_GetText(0x27U));

    sprintf((char*)text, D_801D0E98, Item_Count(group, key, 0U) & HALF_MASK);
    UI_DrawGlyphString((task->pos.x + 137), (task->pos.y + 35), 0U, text);
    UI_DrawText((task->pos.x + 14), (task->pos.y + 45), 0, 0xFFU, Resource_GetText(0x28U));

    sprintf((char*)text, D_801D0E98, Item_Count(group, key, 1U) & HALF_MASK);
    UI_DrawGlyphString((task->pos.x + 137), (task->pos.y + 48), 0U, text);

    GFX_AddDrawMode(GetTPage(0, 0, 896, 256) & HALF_MASK);

    for (index = 0; index < 20; index++) {
        UI_DrawSprite((task->pos.x + (index + 1) * 8), task->pos.y, 0x29, 0);
        UI_DrawSprite((task->pos.x + (index + 1) * 8), (task->pos.y + 56), 0x3B, 0);
    }
    for (index = 0; index < 6; index++) {
        UI_DrawSprite(task->pos.x, (task->pos.y + (index + 1) * 8), 0x2B, 0);
        UI_DrawSprite((task->pos.x + 168), (task->pos.y + (index + 1) * 8), 0x2C, 0);
    }

    UI_DrawSprite(task->pos.x, task->pos.y, 0x28, 0);
    UI_DrawSprite((task->pos.x + 168), task->pos.y, 0x2A, 0);
    UI_DrawSprite(task->pos.x, (task->pos.y + 56), 0x3A, 0);
    UI_DrawSprite((task->pos.x + 168), (task->pos.y + 56), 0x3C, 0);
}
