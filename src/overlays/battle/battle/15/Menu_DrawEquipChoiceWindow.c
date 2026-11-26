#include "battle_15.h"
#include "menu/inventory.h"
#include "sys/exe.h"

/* The battle copy of the equip list: seven visible rows and a shorter frame. */
/* func_800B3AE8 */
MATCH void Menu_DrawEquipChoiceWindow(MenuPanelTask* task) {
    u8   scroll_y;
    u8   scroll_rows;
    u8   slot;
    u8   choices;
    u8   i;
    u8*  ids;
    u8*  counts;
    s16  y;
    u8   first;
    u8** title;
    u8   length;
    s32  title_x;

    switch (task->unk_09) {
        case EQUIP_SLOT_WEAPON:
        default:
            task->unk_08 = ITEM_CATEGORY_WEAPON;
            break;
        case EQUIP_SLOT_SHIELD:
        case EQUIP_SLOT_HELMET:
        case EQUIP_SLOT_ARMOR:
            task->unk_08 = ITEM_CATEGORY_ARMOR;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
        case EQUIP_SLOT_ACCESSORY_2:
            task->unk_08 = ITEM_CATEGORY_ACCESSORY;
            break;
    }

    i       = 0;
    choices = 0;
    ids     = g_ItemCategoryIds[task->unk_08];
    counts  = g_ItemCategoryCounts[task->unk_08];
    for (slot = 0; slot < INV_SLOTS_PER_CATEGORY; slot++) {
        if ((Item_PassesTest(ITEM_TEST_EQUIPPABLE, g_CharSlot[g_PartyBattleOrder[task->unk_0C]], task->unk_08, *ids) & BYTE_MASK) &&
            (task->unk_08 != ITEM_CATEGORY_ARMOR || task->unk_09 - EQUIP_SLOT_SHIELD == (Item_GetIcon(ITEM_CATEGORY_ARMOR, *ids) & BYTE_MASK) - ITEM_TYPE_SHIELD)) {
            choices++;
            g_MenuEquipChoiceIds[i]    = *ids;
            g_MenuEquipChoiceCounts[i] = *counts;
            i++;
        }
        ids++;
        counts++;
    }
    for (; i < INV_SLOTS_PER_CATEGORY; i++) {
        g_MenuEquipChoiceIds[i]    = 0;
        g_MenuEquipChoiceCounts[i] = 0;
    }
    task->flags = g_MenuEquipChoiceIds[task->unk_0B];

    UI_WindowDraw(task->pos.x + 3, task->pos.y + 3, 153, 130, 0, CHARACTER_BLOCK->window_style);
    first  = UI_ScrollList(&task->unk_0A, &scroll_y, &scroll_rows, (u8*)&task->u.addr.unk_10);
    ids    = &g_MenuEquipChoiceIds[first];
    counts = &g_MenuEquipChoiceCounts[first];
    y      = task->pos.y + (s8)scroll_y;
    for (i = 0; i < scroll_rows + 7; i++) {
        if (*ids != 0) {
            if (task->unk_0A + i == task->unk_0B) {
                UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 26), UI_TEXT_DIM, task->unk_08, *ids, *counts, true);
                UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 24), UI_TEXT_NORMAL, task->unk_08, *ids, *counts, false);
            } else {
                UI_ListDrawItemRow(task->pos.x + 7, (s16)(y + 26), UI_TEXT_NORMAL, task->unk_08, *ids, *counts, false);
            }
        }
        ids++;
        counts++;
        y += 13;
    }

    UI_WindowDraw(task->pos.x + 3, task->pos.y + 3, 153, 20, 0, CHARACTER_BLOCK->window_style);
    UI_WindowDraw(task->pos.x + 3, task->pos.y + 122, 153, 8, 0, CHARACTER_BLOCK->window_style);
    title   = &g_MenuEquipTitles[task->unk_08];
    length  = Game_ReadCommand(*title);
    title_x = length * 4 - 78;
    UI_TextDraw(task->pos.x - title_x, task->pos.y + 7, UI_TEXT_NORMAL, MENU_LABEL_LENGTH, *title);
    sprintf(g_UiTextFormatBuffer, g_MenuInventoryCountFormat, choices, INV_SLOTS_PER_CATEGORY);
    UI_TextDrawGlyphString(task->pos.x + 85, task->pos.y + 122, UI_TEXT_NORMAL, g_UiTextFormatBuffer);

    UI_SpriteDrawRun(task->pos.x, task->pos.y, s_BattleAbilityLine1Run, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(task->pos.x, task->pos.y, s_BattleAbilityLine2Run, UI_SPRITE_ALT_PAGE);

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
    UI_SpriteDraw(task->pos.x + 8, task->pos.y, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(task->pos.x + 144, task->pos.y, 0x33, UI_SPRITE_ALT_PAGE);

    UI_ListDrawScrollbar(g_MenuEquipChoiceIds, task->unk_0A, task->pos.x + 144, task->pos.y + 24, 7, INV_SLOTS_PER_CATEGORY, 92);
}
