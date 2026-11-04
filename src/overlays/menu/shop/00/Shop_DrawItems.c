#include "shop_00.h"

MATCH void Shop_DrawItems(ShopPanel* panel) {
    u8* names;
    u8* entry;
    s32 y;
    u8  index;
    s32 price;
    s32 icon;
    u8* resource;
    u8  group;
    u8  item;
    u8  color;
    u8  dim;

    UI_DrawWindow(panel->x + 3, panel->y + 3, 173, 159, panel->unk_0A, D_80144952);
    names = panel->names;
    y     = panel->y + 8;
    for (index = 0; index < names[0]; index++) {
        entry    = names + index * 2;
        group    = entry[1];
        item     = entry[2];
        price    = Shop_ApplyPercent(Item_GetPrice(group, item), panel->unk_0B);
        icon     = Item_GetKind(group, item);
        resource = Item_GetRecord(group, item);
        if (panel->unk_0A != 0 || g_Zenny < (u32)price) {
            color = 7;
            dim   = 1;
        } else {
            color = 0;
            dim   = 0;
        }
        sprintf((s8*)g_UiFormatBuffer, D_801D0E88, price);
        if (index == panel->unk_0C) {
            if (color == 0) {
                func_801AEA80((u16)(panel->x + 4), (u16)(y + 3), D_801E5E0C[(u8)icon], 1);
                UI_DrawText(panel->x + 14, y, 7, (u8)func_801AF20C(resource), resource);
                UI_DrawGlyphString(panel->x + 113, y + 3, 7, g_UiFormatBuffer);
            }
            y -= 2;
        }
        func_801AEA80((u16)(panel->x + 4), (u16)(y + 3), D_801E5E0C[(u8)icon], dim);
        UI_DrawText(panel->x + 14, y, color, (u8)func_801AF20C(resource), resource);
        UI_DrawGlyphString(panel->x + 113, y + 3, color, g_UiFormatBuffer);
        if (index == panel->unk_0C) {
            y += 2;
        }
        y += 0xD;
    }
    Menu_DrawPanelFrame(panel->x, panel->y, 0x14, 0x13);
}
