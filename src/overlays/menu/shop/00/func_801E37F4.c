#include "shop_00.h"

/* The description panel's frame is this wide and this tall. */
#define SHOP_DESC_PANEL_WIDTH    0xAA
#define SHOP_DESC_PANEL_HEIGHT   0x1C
/* The border sprite rows along the panel's top and bottom edges. */
#define SHOP_DESC_BORDER_COLUMNS 20
#define SHOP_DESC_BORDER_ROWS    2
/* Each border sprite is one cell wide. */
#define SHOP_DESC_BORDER_STRIDE  8
/* Layout in pixels: the window, the lines inside it and the frame edges. */
#define SHOP_DESC_SHADOW_OFFSET  3
#define SHOP_DESC_ICON_X         7
#define SHOP_DESC_ICON_Y         6
#define SHOP_DESC_NAME_X         17
#define SHOP_DESC_NAME_Y         4
#define SHOP_DESC_PRICE_X        113
#define SHOP_DESC_PRICE_Y        7
#define SHOP_DESC_TOTAL_X        105
#define SHOP_DESC_LINE2_Y        18
#define SHOP_DESC_QUANTITY_X     14
#define SHOP_DESC_BOTTOM_Y       24
#define SHOP_DESC_RIGHT_X        168

/* The shared panel task names the shop fields only by offset: unk_06 is the
 * panel's y origin, unk_0A the item category, unk_0B the item id, unk_0C the
 * quantity (the "*%2d" line) and unk_0D the discount flag. */

MATCH void func_801E37F4(MenuPanelTask* task) {
    char* buffer;
    u8*   record;
    u32   price;
    u8    category;
    u8    item_id;
    u8    discount;
    u8    i;
    s16   offset;

    discount = task->flags;
    category = task->unk_0A;
    item_id  = task->unk_0B;
    price    = Shop_GetSellPrice(category, item_id, discount);
    record   = Item_GetRecord(category, item_id);
    UI_DrawWindow((task->pos.x + SHOP_DESC_SHADOW_OFFSET) & HALF_MASK, (task->pos.y + SHOP_DESC_SHADOW_OFFSET) & HALF_MASK, SHOP_DESC_PANEL_WIDTH, SHOP_DESC_PANEL_HEIGHT, 0, g_WindowStyle);
    func_801AEA80((task->pos.x + SHOP_DESC_ICON_X) & HALF_MASK, (task->pos.y + SHOP_DESC_ICON_Y) & HALF_MASK, D_801E5E38[Item_GetIcon(category, item_id) & BYTE_MASK], 0);
    UI_DrawText(task->pos.x + SHOP_DESC_NAME_X, task->pos.y + SHOP_DESC_NAME_Y, 0, Game_ReadCommand(record) & BYTE_MASK, record);
    buffer = (char*)g_UiFormatBuffer;
    TEXT_Format(buffer, D_801D0E88, price);
    UI_DrawGlyphString(task->pos.x + SHOP_DESC_PRICE_X, task->pos.y + SHOP_DESC_PRICE_Y, 0, buffer);
    TEXT_Format(buffer, D_801D0E90, price * task->unk_0C);
    UI_DrawGlyphString(task->pos.x + SHOP_DESC_TOTAL_X, task->pos.y + SHOP_DESC_LINE2_Y, 0, buffer);
    TEXT_Format(buffer, D_801D0E98, task->unk_0C);
    UI_DrawGlyphString(task->pos.x + SHOP_DESC_QUANTITY_X, task->pos.y + SHOP_DESC_LINE2_Y, 0, buffer);
    GFX_AddDrawMode(GetTPage(0, 0, 896, 256) & HALF_MASK);
    for (i = 0; i < SHOP_DESC_BORDER_COLUMNS; i++) {
        offset = (i + 1) * SHOP_DESC_BORDER_STRIDE;
        UI_DrawSprite(task->pos.x + offset, task->pos.y, MENU_FRAME_SPRITE_TOP, 0);
        UI_DrawSprite(task->pos.x + offset, task->pos.y + SHOP_DESC_BOTTOM_Y, MENU_FRAME_SPRITE_FLAT_BOTTOM, 0);
    }
    for (i = 0; i < SHOP_DESC_BORDER_ROWS; i++) {
        offset = (i + 1) * SHOP_DESC_BORDER_STRIDE;
        UI_DrawSprite(task->pos.x, task->pos.y + offset, MENU_FRAME_SPRITE_LEFT, 0);
        UI_DrawSprite(task->pos.x + SHOP_DESC_RIGHT_X, task->pos.y + offset, MENU_FRAME_SPRITE_RIGHT, 0);
    }
    UI_DrawSprite(task->pos.x, task->pos.y, MENU_FRAME_SPRITE_TOP_LEFT, 0);
    UI_DrawSprite(task->pos.x + SHOP_DESC_RIGHT_X, task->pos.y, MENU_FRAME_SPRITE_TOP_RIGHT, 0);
    UI_DrawSprite(task->pos.x, task->pos.y + SHOP_DESC_BOTTOM_Y, MENU_FRAME_SPRITE_FLAT_BOTTOM_LEFT, 0);
    UI_DrawSprite(task->pos.x + SHOP_DESC_RIGHT_X, task->pos.y + SHOP_DESC_BOTTOM_Y, MENU_FRAME_SPRITE_FLAT_BOTTOM_RIGHT, 0);
}
