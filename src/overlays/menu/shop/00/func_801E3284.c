#include "shop_00.h"

/* Layout in pixels: the window, the lines inside it and the frame cells around it. */
#define SHOP_COUNTS_SHADOW_OFFSET    3
#define SHOP_COUNTS_WINDOW_WIDTH     170
#define SHOP_COUNTS_WINDOW_HEIGHT    60
#define SHOP_COUNTS_ICON_X           4
#define SHOP_COUNTS_ICON_Y           7
#define SHOP_COUNTS_NAME_X           14
#define SHOP_COUNTS_NAME_Y           4
#define SHOP_COUNTS_TOTAL_X          105
#define SHOP_COUNTS_TOTAL_Y          18
#define SHOP_COUNTS_NUMBER_X         137
#define SHOP_COUNTS_QUANTITY_Y       7
#define SHOP_COUNTS_HELD_LABEL_Y     32
#define SHOP_COUNTS_HELD_Y           35
#define SHOP_COUNTS_EQUIPPED_LABEL_Y 45
#define SHOP_COUNTS_EQUIPPED_Y       48
#define SHOP_COUNTS_FRAME_COLUMNS    20
#define SHOP_COUNTS_FRAME_ROWS       6
#define SHOP_COUNTS_FRAME_CELL       8
#define SHOP_COUNTS_FRAME_BOTTOM_Y   56
#define SHOP_COUNTS_FRAME_RIGHT_X    168

/* The text resources labelling the two count lines, and the Item_Count mode of each. */
#define SHOP_TEXT_HELD_LABEL         0x27
#define SHOP_TEXT_EQUIPPED_LABEL     0x28
#define ITEM_COUNT_MODE_HELD         0
#define ITEM_COUNT_MODE_EQUIPPED     1

MATCH void func_801E3284(MenuPanelTask* task) {
    u8* entry;
    u8* icon;
    u8  group;
    u8  key;
    u8  index;
    s32 price;
    u8* text;

    entry = (u8*)task->item_table + task->unk_0B * 2;
    group = entry[1];
    key   = entry[2];

    price = Shop_ApplyPercent(Item_GetPrice(group, key) & HALF_MASK, task->unk_0A);
    icon  = Item_GetRecord(group, key);

    UI_WindowDraw((task->pos.vx + SHOP_COUNTS_SHADOW_OFFSET) & HALF_MASK, (task->pos.vy + SHOP_COUNTS_SHADOW_OFFSET) & HALF_MASK, SHOP_COUNTS_WINDOW_WIDTH, SHOP_COUNTS_WINDOW_HEIGHT, 0,
                  g_WindowStyle);
    UI_IconDraw(((u16)task->pos.vx + SHOP_COUNTS_ICON_X) & HALF_MASK, ((u16)task->pos.vy + SHOP_COUNTS_ICON_Y) & HALF_MASK, D_801E5E1C[Item_GetIcon(group, key) & BYTE_MASK], 0);
    UI_TextDraw((task->pos.vx + SHOP_COUNTS_NAME_X), (task->pos.vy + SHOP_COUNTS_NAME_Y), 0, Game_ReadCommand(icon) & BYTE_MASK, icon);

    text = g_UiTextFormatBuffer;
    TEXT_Format(text, D_801D0E90, price * task->unk_0C);
    UI_TextDrawGlyphString((task->pos.vx + SHOP_COUNTS_TOTAL_X), (task->pos.vy + SHOP_COUNTS_TOTAL_Y), 0U, text);

    TEXT_Format(text, D_801D0E98, task->unk_0C);
    UI_TextDrawGlyphString((task->pos.vx + SHOP_COUNTS_NUMBER_X), (task->pos.vy + SHOP_COUNTS_QUANTITY_Y), 0U, text);
    UI_TextDraw((task->pos.vx + SHOP_COUNTS_NAME_X), (task->pos.vy + SHOP_COUNTS_HELD_LABEL_Y), 0, TEXT_LENGTH_MAX, UI_MessageGetText(SHOP_TEXT_HELD_LABEL));

    TEXT_Format(text, D_801D0E98, Item_Count(group, key, ITEM_COUNT_MODE_HELD) & HALF_MASK);
    UI_TextDrawGlyphString((task->pos.vx + SHOP_COUNTS_NUMBER_X), (task->pos.vy + SHOP_COUNTS_HELD_Y), 0U, text);
    UI_TextDraw((task->pos.vx + SHOP_COUNTS_NAME_X), (task->pos.vy + SHOP_COUNTS_EQUIPPED_LABEL_Y), 0, TEXT_LENGTH_MAX, UI_MessageGetText(SHOP_TEXT_EQUIPPED_LABEL));

    TEXT_Format(text, D_801D0E98, Item_Count(group, key, ITEM_COUNT_MODE_EQUIPPED) & HALF_MASK);
    UI_TextDrawGlyphString((task->pos.vx + SHOP_COUNTS_NUMBER_X), (task->pos.vy + SHOP_COUNTS_EQUIPPED_Y), 0U, text);

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256) & HALF_MASK);

    for (index = 0; index < SHOP_COUNTS_FRAME_COLUMNS; index++) {
        UI_SpriteDraw((task->pos.vx + (index + 1) * SHOP_COUNTS_FRAME_CELL), task->pos.vy, MENU_FRAME_SPRITE_TOP, 0);
        UI_SpriteDraw((task->pos.vx + (index + 1) * SHOP_COUNTS_FRAME_CELL), (task->pos.vy + SHOP_COUNTS_FRAME_BOTTOM_Y), MENU_FRAME_SPRITE_FLAT_BOTTOM, 0);
    }
    for (index = 0; index < SHOP_COUNTS_FRAME_ROWS; index++) {
        UI_SpriteDraw(task->pos.vx, (task->pos.vy + (index + 1) * SHOP_COUNTS_FRAME_CELL), MENU_FRAME_SPRITE_LEFT, 0);
        UI_SpriteDraw((task->pos.vx + SHOP_COUNTS_FRAME_RIGHT_X), (task->pos.vy + (index + 1) * SHOP_COUNTS_FRAME_CELL), MENU_FRAME_SPRITE_RIGHT, 0);
    }

    UI_SpriteDraw(task->pos.vx, task->pos.vy, MENU_FRAME_SPRITE_TOP_LEFT, 0);
    UI_SpriteDraw((task->pos.vx + SHOP_COUNTS_FRAME_RIGHT_X), task->pos.vy, MENU_FRAME_SPRITE_TOP_RIGHT, 0);
    UI_SpriteDraw(task->pos.vx, (task->pos.vy + SHOP_COUNTS_FRAME_BOTTOM_Y), MENU_FRAME_SPRITE_FLAT_BOTTOM_LEFT, 0);
    UI_SpriteDraw((task->pos.vx + SHOP_COUNTS_FRAME_RIGHT_X), (task->pos.vy + SHOP_COUNTS_FRAME_BOTTOM_Y), MENU_FRAME_SPRITE_FLAT_BOTTOM_RIGHT, 0);
}
