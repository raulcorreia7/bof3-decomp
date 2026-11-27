#include "shop_00.h"

/* Layout in pixels: the window, the rows inside it and the frame cells around it. */
#define SHOP_ITEM_LIST_SHADOW_OFFSET 3
#define SHOP_ITEM_LIST_WINDOW_WIDTH  173
#define SHOP_ITEM_LIST_WINDOW_HEIGHT 159
#define SHOP_ITEM_LIST_FIRST_ROW_Y   8
#define SHOP_ITEM_LIST_ROW_HEIGHT    13
#define SHOP_ITEM_LIST_ICON_X        4
#define SHOP_ITEM_LIST_NAME_X        14
#define SHOP_ITEM_LIST_PRICE_X       113
#define SHOP_ITEM_LIST_TEXT_DY       3
#define SHOP_ITEM_LIST_SELECTED_RISE 2
#define SHOP_ITEM_LIST_FRAME_WIDTH   20
#define SHOP_ITEM_LIST_FRAME_HEIGHT  19

/* The dim flag of the row's item icon. */
#define SHOP_ITEM_ICON_ENABLED       0
#define SHOP_ITEM_ICON_DIMMED        1

MATCH void Shop_DrawItems(MenuListPanel* panel) {
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

    UI_WindowDraw(panel->pos.x + SHOP_ITEM_LIST_SHADOW_OFFSET, panel->pos.y + SHOP_ITEM_LIST_SHADOW_OFFSET, SHOP_ITEM_LIST_WINDOW_WIDTH, SHOP_ITEM_LIST_WINDOW_HEIGHT, panel->source.items.dimmed,
                  g_WindowStyle);

    names = panel->names;
    y     = panel->pos.y + SHOP_ITEM_LIST_FIRST_ROW_Y;
    for (index = 0; index < names[0]; index++) {
        entry    = names + index * 2;
        group    = entry[1];
        item     = entry[2];
        price    = Shop_ApplyPercent(Item_GetPrice(group, item), panel->source.items.price_percent);
        icon     = Item_GetIcon(group, item);
        resource = Item_GetRecord(group, item);
        if (panel->source.items.dimmed != 0 || g_Zenny < price) {
            color = UI_TEXT_DIM;
            dim   = SHOP_ITEM_ICON_DIMMED;
        } else {
            color = UI_TEXT_NORMAL;
            dim   = SHOP_ITEM_ICON_ENABLED;
        }

        TEXT_Format(g_UITextFormatBuffer, D_801D0E88, price);
        if (index == panel->unk_0C) {
            if (color == UI_TEXT_NORMAL) {
                UI_IconDraw((u16)(panel->pos.x + SHOP_ITEM_LIST_ICON_X), (u16)(y + SHOP_ITEM_LIST_TEXT_DY), D_801E5E0C[(u8)icon], SHOP_ITEM_ICON_DIMMED);
                UI_TextDraw(panel->pos.x + SHOP_ITEM_LIST_NAME_X, y, UI_TEXT_DIM, (u8)Game_ReadCommand(resource), resource);
                UI_TextDrawGlyphString(panel->pos.x + SHOP_ITEM_LIST_PRICE_X, y + SHOP_ITEM_LIST_TEXT_DY, UI_TEXT_DIM, g_UITextFormatBuffer);
            }
            y -= SHOP_ITEM_LIST_SELECTED_RISE;
        }

        UI_IconDraw((u16)(panel->pos.x + SHOP_ITEM_LIST_ICON_X), (u16)(y + SHOP_ITEM_LIST_TEXT_DY), D_801E5E0C[(u8)icon], dim);
        UI_TextDraw(panel->pos.x + SHOP_ITEM_LIST_NAME_X, y, color, (u8)Game_ReadCommand(resource), resource);
        UI_TextDrawGlyphString(panel->pos.x + SHOP_ITEM_LIST_PRICE_X, y + SHOP_ITEM_LIST_TEXT_DY, color, g_UITextFormatBuffer);
        if (index == panel->unk_0C) {
            y += SHOP_ITEM_LIST_SELECTED_RISE;
        }
        y += SHOP_ITEM_LIST_ROW_HEIGHT;
    }

    Menu_DrawPanelFrame(panel->pos.x, panel->pos.y, SHOP_ITEM_LIST_FRAME_WIDTH, SHOP_ITEM_LIST_FRAME_HEIGHT);
}
