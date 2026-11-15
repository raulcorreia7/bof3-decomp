#include "battle_15.h"
#include "menu/inventory.h"

/* The battle copy of the menu inventory panel: seven visible rows and a shorter frame, without the vital-tab marks. */
/* func_800B25C0 */
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

    UI_DrawWindow(task->pos.x + 3, task->pos.y + 3, 153, 130, task->unk_09, g_WindowStyle);
    first  = func_801AFD10(&task->unk_0B, &scroll_y, &scroll_rows, (u8*)&task->u.list.scroll);
    y      = task->pos.y + (s8)scroll_y;
    ids    = D_801C893C[task->unk_0A] + first;
    counts = D_801C8950[task->unk_0A] + first;
    for (i = 0; i < scroll_rows + 7; i++) {
        item = *ids;
        if (item != 0) {
            unusable = false;
            if (task->unk_09 != 0 || (func_801AF494(task->unk_08, g_CharSlot[g_PartyBattleOrder[(s8)D_80148656]], task->unk_0A, item) & BYTE_MASK) == 0) {
                unusable = true;
            }
            dim   = unusable;
            shade = -dim & MENU_SHADE_DIM;
            row   = task->unk_0B + i;
            if (row == task->flags) {
                shade = MENU_SHADE_SELECTED;
            }
            row_shade = shade;
            held      = 1;
            if (task->unk_0A != ITEM_CAT_VITAL) {
                held = *counts;
            }
            if (row == task->flags || row == task->unk_0C) {
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

    UI_DrawWindow(task->pos.x + 3, task->pos.y + 3, 153, 20, task->unk_09, CHARACTER_BLOCK->window_style);
    UI_DrawWindow(task->pos.x + 3, task->pos.y + 122, 153, 8, task->unk_09, CHARACTER_BLOCK->window_style);
    title   = &g_MenuInventoryTitles[task->unk_0A];
    length  = Game_ReadCommand(*title);
    title_x = length * 4 - 78;
    UI_DrawText(task->pos.x - title_x, task->pos.y + 7, -(task->unk_09 != 0) & MENU_SHADE_DIM, 16, *title);
    sprintf(g_UiFormatBuffer, g_MenuInventoryCountFormat, Item_CountHeld(task->unk_0A) & BYTE_MASK, task->unk_0A != ITEM_CAT_VITAL ? INV_SLOTS_PER_CATEGORY : INV_VITAL_ITEM_SLOTS);
    UI_DrawGlyphString(task->pos.x + 85, task->pos.y + 122, -(task->unk_09 != 0) & MENU_SHADE_DIM, g_UiFormatBuffer);

    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_2) ? s_BattleAbilityLine1FlagRun : s_BattleAbilityLine1Run, 1);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & MENU_LIST_FLAG_TAB_1) ? s_BattleAbilityLine2FlagRun : s_BattleAbilityLine2Run, 1);
    tabs = task->u.list.tabs;
    if ((tabs & MENU_LIST_FRAME_MASK) == 0) {
        task->u.list.tabs = 0;
    } else {
        task->u.list.tabs = tabs - MENU_LIST_FRAME_STEP;
    }

    for (i = 0; i < 10; i++) {
        UI_DrawSprite(task->pos.x + (i + 5) * 8, task->pos.y, 1, 1);
    }
    for (i = 0; i < 12; i++) {
        UI_DrawSprite(task->pos.x, task->pos.y + (i + 3) * 8, 4, 1);
    }
    UI_DrawSprite(task->pos.x + 144, task->pos.y + 24, 0x16, 1);
    for (i = 0; i < 9; i++) {
        UI_DrawSprite(task->pos.x + 144, task->pos.y + (i + 5) * 8, 0x17, 1);
    }
    UI_DrawSprite(task->pos.x + 144, task->pos.y + 112, 0x18, 1);
    UI_DrawSprite(task->pos.x, task->pos.y + 120, 0x19, 1);
    for (i = 0; i < 9; i++) {
        UI_DrawSprite(task->pos.x + (i + 1) * 8, task->pos.y + 120, 0x1A, 1);
    }
    UI_DrawSprite(task->pos.x + 80, task->pos.y + 120, 0x1B, 1);
    for (i = 0; i < 6; i++) {
        UI_DrawSprite(task->pos.x + (i + 11) * 8, task->pos.y + 120, 0x1C, 1);
    }
    UI_DrawSprite(task->pos.x + 136, task->pos.y + 120, 0x1D, 1);

    func_801AFA1C(D_801C893C[task->unk_0A], task->unk_0B, task->pos.x + 144, task->pos.y + 24, 7, INV_SLOTS_PER_CATEGORY, 92);
}
