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
    s32  shade;
    u8   row_shade;
    s32  row;
    u8** title;
    u8*  ids;
    u8*  counts;
    u16  tabs;
    u8   length;
    s32  title_x;
    u8   scroll_shift;

    UI_DrawWindow(task->pos.x + 3, task->pos.y + 3, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    first  = func_801AFD10(&task->unk_0B, &scroll_y, &scroll_rows, (u8*)&task->u.list.scroll);
    y      = task->pos.y + (s8)scroll_y;
    ids    = D_801C893C[task->unk_0A] + first;
    counts = D_801C8950[task->unk_0A] + first;
    for (i = 0; i < scroll_rows + 9; i++) {
        item = *ids;
        if (item != 0) {
            unusable = false;
            if (task->unk_09 != 0 || (func_801AF494(task->unk_08, g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], task->unk_0A, item) & BYTE_MASK) == 0) {
                unusable = true;
            }
            dim   = unusable;
            shade = -dim & MENU_SHADE_DIM;
            if (((s16)task->u.list.scroll >> 4) != 0xF) {
                scroll_shift = scroll_rows;
            } else {
                scroll_shift = 0;
            }
            row = task->unk_0B + i;
            if (row == task->flags + scroll_shift) {
                shade = MENU_SHADE_SELECTED;
            }
            row_shade = shade;
            held      = 1;
            if (task->unk_0A != ITEM_CAT_VITAL) {
                held = *counts;
            }
            if (row == task->flags + scroll_shift || row == task->unk_0C + scroll_shift) {
                if (row_shade != MENU_SHADE_DIM) {
                    func_801AF800(task->pos.x + 7, (s16)(y + 26), MENU_SHADE_DIM, task->unk_0A, *ids, held, true);
                }
                func_801AF800(task->pos.x + 7, (s16)(y + 24), row_shade, task->unk_0A, *ids, held, dim);
            } else {
                func_801AF800(task->pos.x + 7, (s16)(y + 26), row_shade, task->unk_0A, *ids, held, dim);
            }
        }
        ids++;
        counts++;
        y += 13;
    }

    UI_DrawWindow(task->pos.x + 3, task->pos.y + 3, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    UI_DrawWindow(task->pos.x + 3, task->pos.y + 146, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, task->unk_09, CHARACTER_BLOCK->window_style);
    title   = &g_MenuInventoryTitles[task->unk_0A];
    length  = Game_ReadCommand(*title);
    title_x = length * 4 - 78;
    UI_DrawText(task->pos.x - title_x, task->pos.y + 7, -(task->unk_09 != 0) & MENU_SHADE_DIM, 16, *title);
    sprintf(g_UiFormatBuffer, g_MenuInventoryCountFormat, Item_CountHeld(task->unk_0A) & BYTE_MASK, task->unk_0A != ITEM_CAT_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS);
    UI_DrawGlyphString(task->pos.x + 85, task->pos.y + 146, -(task->unk_09 != 0) & MENU_SHADE_DIM, g_UiFormatBuffer);

    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, 1);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_1) ? g_MenuInventoryTab1OnSprites : g_MenuInventoryTab1OffSprites, 1);
    tabs = task->u.list.tabs;
    if ((tabs & MENU_LIST_FRAME_MASK) == 0) {
        task->u.list.tabs = 0;
    } else {
        task->u.list.tabs = tabs - MENU_LIST_FRAME_STEP;
    }

    for (i = 0; i < 10; i++) {
        UI_DrawSprite(task->pos.x + (i + 5) * 8, task->pos.y, 1, 1);
    }
    for (i = 0; i < 15; i++) {
        UI_DrawSprite(task->pos.x, task->pos.y + (i + 3) * 8, 4, 1);
    }
    UI_DrawSprite(task->pos.x + 144, task->pos.y + 24, 0x16, 1);
    for (i = 0; i < 12; i++) {
        UI_DrawSprite(task->pos.x + 144, task->pos.y + (i + 5) * 8, 0x17, 1);
    }
    UI_DrawSprite(task->pos.x + 144, task->pos.y + 136, 0x18, 1);
    UI_DrawSprite(task->pos.x, task->pos.y + 144, 0x19, 1);
    for (i = 0; i < 9; i++) {
        UI_DrawSprite(task->pos.x + (i + 1) * 8, task->pos.y + 144, 0x1A, 1);
    }
    UI_DrawSprite(task->pos.x + 80, task->pos.y + 144, 0x1B, 1);
    for (i = 0; i < 6; i++) {
        UI_DrawSprite(task->pos.x + (i + 11) * 8, task->pos.y + 144, 0x1C, 1);
    }
    UI_DrawSprite(task->pos.x + 136, task->pos.y + 144, 0x1D, 1);
    if (task->unk_0A == ITEM_CAT_VITAL) {
        UI_DrawSprite(task->pos.x + 8, task->pos.y, 0x32, 1);
        UI_DrawSprite(task->pos.x + 144, task->pos.y, 0x33, 1);
    }

    func_801AFA1C(D_801C893C[task->unk_0A], task->unk_0B, task->pos.x + 144, task->pos.y + 24, 9, task->unk_0A != ITEM_CAT_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS, 116);
}
