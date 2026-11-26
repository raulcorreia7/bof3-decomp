#include "battle_15.h"
#include "menu/inventory.h"

/* The battle copy of the menu inventory panel: seven visible lines and a shorter frame, without the vital-tab marks. */
/* func_800B25C0 */
MATCH void Menu_DrawInventoryWindow(MenuPanelTask* task) {
    u8   scroll_y;
    u8   line_count;
    u8   item;
    s32  dim;
    u8   i;
    u8   held;
    u8   unusable;
    s16  y;
    u8   first;
    s32  shade;
    u8   line_shade;
    s32  line;
    u8** title;
    u8*  ids;
    u8*  counts;
    u16  tabs;
    u8   length;
    s32  title_x;

    UI_WindowDraw(task->pos.x + 3, task->pos.y + 3, 153, 130, task->unk_09, g_WindowStyle);
    first  = UI_ScrollList(&task->unk_0B, &scroll_y, &line_count, (u8*)&task->u.list.scroll);
    y      = task->pos.y + (s8)scroll_y;
    ids    = g_ItemCategoryIds[task->unk_0A] + first;
    counts = g_ItemCategoryCounts[task->unk_0A] + first;
    for (i = 0; i < line_count + 7; i++) {
        item = *ids;
        if (item != 0) {
            unusable = false;
            if (task->unk_09 != 0 || (Item_PassesTest(task->unk_08, g_CharSlot[g_PartyBattleOrder[(s8)D_80148656]], task->unk_0A, item) & BYTE_MASK) == 0) {
                unusable = true;
            }
            dim   = unusable;
            shade = -dim & UI_TEXT_DIM;
            line  = task->unk_0B + i;
            if (line == task->flags) {
                shade = UI_TEXT_HIGHLIGHT;
            }
            line_shade = shade;
            held       = 1;
            if (task->unk_0A != ITEM_CATEGORY_VITAL) {
                held = *counts;
            }
            if (line == task->flags || line == task->unk_0C) {
                if (line_shade != UI_TEXT_DIM) {
                    UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 26), UI_TEXT_DIM, task->unk_0A, *ids, held, true);
                }
                UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 24), line_shade, task->unk_0A, *ids, held, dim);
            } else {
                UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 26), line_shade, task->unk_0A, *ids, held, dim);
            }
        }
        ids++;
        counts++;
        y += 13;
    }

    UI_WindowDraw(task->pos.x + 3, task->pos.y + 3, 153, 20, task->unk_09, CHARACTER_BLOCK->window_style);
    UI_WindowDraw(task->pos.x + 3, task->pos.y + 122, 153, 8, task->unk_09, CHARACTER_BLOCK->window_style);
    title   = &g_MenuInventoryTitles[task->unk_0A];
    length  = Game_ReadCommand(*title);
    title_x = length * 4 - 78;
    UI_TextDraw(task->pos.x - title_x, task->pos.y + 7, -(task->unk_09 != 0) & UI_TEXT_DIM, MENU_LABEL_LENGTH, *title);
    sprintf(g_UiTextFormatBuffer, g_MenuInventoryCountFormat, Item_CountHeld(task->unk_0A) & BYTE_MASK, task->unk_0A != ITEM_CATEGORY_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS);
    UI_TextDrawGlyphString(task->pos.x + 85, task->pos.y + 122, -(task->unk_09 != 0) & UI_TEXT_DIM, g_UiTextFormatBuffer);

    UI_SpriteDrawRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_2) ? s_BattleAbilityLine1FlagRun : s_BattleAbilityLine1Run, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_1) ? s_BattleAbilityLine2FlagRun : s_BattleAbilityLine2Run, UI_SPRITE_ALT_PAGE);
    tabs = task->u.list.tabs;
    if ((tabs & MENU_LIST_FRAME_MASK) == 0) {
        task->u.list.tabs = 0;
    } else {
        task->u.list.tabs = tabs - MENU_LIST_FRAME_STEP;
    }

    for (i = 0; i < 10; i++) {
        UI_SpriteDraw(task->pos.x + (i + 5) * 8, task->pos.y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw(task->pos.x, task->pos.y + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.x + 144, task->pos.y + 24, 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(task->pos.x + 144, task->pos.y + (i + 5) * 8, 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.x + 144, task->pos.y + 112, 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.x, task->pos.y + 120, 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(task->pos.x + (i + 1) * 8, task->pos.y + 120, 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.x + 80, task->pos.y + 120, 0x1B, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 6; i++) {
        UI_SpriteDraw(task->pos.x + (i + 11) * 8, task->pos.y + 120, 0x1C, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(task->pos.x + 136, task->pos.y + 120, 0x1D, UI_SPRITE_ALT_PAGE);

    UI_ListDrawScrollbar(g_ItemCategoryIds[task->unk_0A], task->unk_0B, task->pos.x + 144, task->pos.y + 24, 7, INV_SLOTS_PER_CATEGORY, 92);
}
