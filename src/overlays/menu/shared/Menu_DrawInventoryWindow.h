/* The inventory panel of the camp, battle-camp, master and shop menus. */
/* needs: type: D_80148656 is read signed here and unsigned by its other readers. */
extern u8 D_80148656;

MATCH void Menu_DrawInventoryWindow(MenuPanelTask* task) {
    u8   scroll_y;
    u8   scroll_rows;
    u8   item;
    s32  dim;
    u8   i;
    u8   held;
    u8   unusable;
    s16  y;
    u8   first;
    s32  shade_value;
    u8   shade;
    s32  row;
    u8** title;
    u8*  ids;
    u8*  counts;
    u16  tabs;
    u8   length;
    s32  title_x;
    u8   scroll_shift;

    UI_WindowDraw(task->pos.vx + 3, task->pos.vy + 3, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    first  = UI_ScrollList(&task->unk_0B, &scroll_y, &scroll_rows, (u8*)&task->u.list.scroll);
    y      = task->pos.vy + (s8)scroll_y;
    ids    = g_ItemCategoryIds[task->unk_0A] + first;
    counts = g_ItemCategoryCounts[task->unk_0A] + first;
    for (i = 0; i < scroll_rows + 9; i++) {
        item = *ids;
        if (item != 0) {
            unusable = false;
            if (task->unk_09 != 0 || (Item_PassesTest(task->unk_08, g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], task->unk_0A, item) & BYTE_MASK) == 0) {
                unusable = true;
            }
            dim         = unusable;
            shade_value = -dim & UI_TEXT_DIM;
            if (((s16)task->u.list.scroll >> 4) != 0xF) {
                scroll_shift = scroll_rows;
            } else {
                scroll_shift = 0;
            }
            row = task->unk_0B + i;
            if (row == task->flags + scroll_shift) {
                shade_value = UI_TEXT_HIGHLIGHT;
            }
            shade = shade_value;
            held  = 1;
            if (task->unk_0A != ITEM_CATEGORY_VITAL) {
                held = *counts;
            }
            if (row == task->flags + scroll_shift || row == task->unk_0C + scroll_shift) {
                if (shade != UI_TEXT_DIM) {
                    UI_ListDrawItemRow(task->pos.vx + 7, (s16)(y + 26), UI_TEXT_DIM, task->unk_0A, *ids, held, true);
                }
                UI_ListDrawItemRow(task->pos.vx + 7, (s16)(y + 24), shade, task->unk_0A, *ids, held, dim);
            } else {
                UI_ListDrawItemRow(task->pos.vx + 7, (s16)(y + 26), shade, task->unk_0A, *ids, held, dim);
            }
        }
        ids++;
        counts++;
        y += 13;
    }

    UI_WindowDraw(task->pos.vx + 3, task->pos.vy + 3, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    UI_WindowDraw(task->pos.vx + 3, task->pos.vy + 146, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    title   = &g_MenuInventoryTitles[task->unk_0A];
    length  = Game_ReadCommand(*title);
    title_x = length * 4 - 78;
    UI_TextDraw(task->pos.vx - title_x, task->pos.vy + 7, -(task->unk_09 != 0) & UI_TEXT_DIM, MENU_LABEL_LENGTH, *title);
    sprintf(g_UiTextFormatBuffer, g_MenuInventoryCountFormat, Item_CountHeld(task->unk_0A) & BYTE_MASK, task->unk_0A != ITEM_CATEGORY_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS);
    UI_TextDrawGlyphString(task->pos.vx + 85, task->pos.vy + 146, -(task->unk_09 != 0) & UI_TEXT_DIM, g_UiTextFormatBuffer);

    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, (task->u.list.tabs & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.vx, task->pos.vy, (task->u.list.tabs & MENU_LIST_FLAG_TAB_1) ? g_MenuInventoryTab1OnSprites : g_MenuInventoryTab1OffSprites, UI_SPRITE_ALT_PAGE);
    tabs = task->u.list.tabs;
    if ((tabs & MENU_LIST_FRAME_MASK) == 0) {
        task->u.list.tabs = 0;
    } else {
        task->u.list.tabs = tabs - MENU_LIST_FRAME_STEP;
    }

    for (i = 0; i < 10; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 5) * 8, task->pos.vy, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 15; i++) {
        UI_SpriteDraw(task->pos.vx, task->pos.vy + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 24, 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + (i + 5) * 8, 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 144, task->pos.vy + 136, 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.vx, task->pos.vy + 144, 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 1) * 8, task->pos.vy + 144, 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 80, task->pos.vy + 144, 0x1B, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 6; i++) {
        UI_SpriteDraw(task->pos.vx + (i + 11) * 8, task->pos.vy + 144, 0x1C, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.vx + 136, task->pos.vy + 144, 0x1D, UI_SPRITE_ALT_PAGE);
    if (task->unk_0A == ITEM_CATEGORY_VITAL) {
        UI_SpriteDraw(task->pos.vx + 8, task->pos.vy, 0x32, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(task->pos.vx + 144, task->pos.vy, 0x33, UI_SPRITE_ALT_PAGE);
    }

    UI_ListDrawScrollbar(g_ItemCategoryIds[task->unk_0A], task->unk_0B, task->pos.vx + 144, task->pos.vy + 24, 9, task->unk_0A != ITEM_CATEGORY_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS,
                         116);
}
