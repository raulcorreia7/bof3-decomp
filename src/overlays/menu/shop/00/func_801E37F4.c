#include "shop_00.h"

/* The description panel's frame is this wide and this tall. */
#define SHOP_DESC_PANEL_WIDTH    0xAA
#define SHOP_DESC_PANEL_HEIGHT   0x1C
/* The border sprite rows along the panel's top and bottom edges. */
#define SHOP_DESC_BORDER_COLUMNS 20
#define SHOP_DESC_BORDER_ROWS    2
/* Each border sprite is one cell wide. */
#define SHOP_DESC_BORDER_STRIDE  8

/* The shared panel task names the shop fields only by offset: unk_06 is the
 * panel's y origin, unk_0A the item kind, unk_0B the item index, unk_0C the
 * quantity (the "*%2d" line) and unk_0D the discount flag. */

MATCH void func_801E37F4(MenuPanelTask* task) {
    char* buffer;
    u8*   record;
    u32   price;
    u8    kind;
    u8    index;
    u8    discount;
    u8    i;
    s16   offset;

    discount = task->flags;
    kind     = task->unk_0A;
    index    = task->unk_0B;
    price    = Shop_GetSellPrice(kind, index, discount);
    record   = Item_GetRecord(kind, index);
    UI_DrawWindow((task->pos.x + 3) & HALF_MASK, (task->pos.y + 3) & HALF_MASK, SHOP_DESC_PANEL_WIDTH,
                  SHOP_DESC_PANEL_HEIGHT, 0, D_80144952);
    func_801AEA80((task->pos.x + 7) & HALF_MASK, (task->pos.y + 6) & HALF_MASK,
                  D_801E5E38[Item_GetKind(kind, index) & BYTE_MASK], 0);
    UI_DrawText(task->pos.x + 17, task->pos.y + 4, 0, func_801AF20C(record) & BYTE_MASK, record);
    buffer = (char*)g_UiFormatBuffer;
    sprintf(buffer, D_801D0E88, price);
    UI_DrawGlyphString(task->pos.x + 113, task->pos.y + 7, 0, buffer);
    sprintf(buffer, D_801D0E90, price * task->unk_0C);
    UI_DrawGlyphString(task->pos.x + 105, task->pos.y + 18, 0, buffer);
    sprintf(buffer, D_801D0E98, task->unk_0C);
    UI_DrawGlyphString(task->pos.x + 14, task->pos.y + 18, 0, buffer);
    GFX_AddDrawMode(GetTPage(0, 0, 896, 256) & HALF_MASK);
    for (i = 0; i < SHOP_DESC_BORDER_COLUMNS; i++) {
        offset = (i + 1) * SHOP_DESC_BORDER_STRIDE;
        UI_DrawSprite(task->pos.x + offset, task->pos.y, 0x29, 0);
        UI_DrawSprite(task->pos.x + offset, task->pos.y + 24, 0x3B, 0);
    }
    for (i = 0; i < SHOP_DESC_BORDER_ROWS; i++) {
        offset = (i + 1) * SHOP_DESC_BORDER_STRIDE;
        UI_DrawSprite(task->pos.x, task->pos.y + offset, 0x2B, 0);
        UI_DrawSprite(task->pos.x + 168, task->pos.y + offset, 0x2C, 0);
    }
    UI_DrawSprite(task->pos.x, task->pos.y, 0x28, 0);
    UI_DrawSprite(task->pos.x + 168, task->pos.y, 0x2A, 0);
    UI_DrawSprite(task->pos.x, task->pos.y + 24, 0x3A, 0);
    UI_DrawSprite(task->pos.x + 168, task->pos.y + 24, 0x3C, 0);
}
