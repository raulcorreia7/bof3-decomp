#include "shop_00.h"

MATCH void func_801D28D0(void) {
    s32              item_index;
    s32              buttons;
    u32              row_limit;
    u32              row_count;
    MenuChoicePanel* panel;
    u8               item_entry;
    u8               new_row;
    u8               old_cursor;
    u16              panel_x;
    u8               initial_cursor;
    u8               initial_first;
    s32              row_offset;
    u8               selected_item;
    u8               selected_cursor;
    u8*              counter;

    panel              = (MenuChoicePanel*)&D_8014842C;
    item_index         = panel->group & BYTE_MASK;
    item_entry         = D_801C893C[item_index][panel->group_cursor];
    g_ShopItemCategory = panel->group;
    g_ShopItemId       = item_entry;
    D_80148340         = Item_GetDescription(item_index, item_entry);
    D_80148435         = 0;
    if (D_8014842F == 0) {
        D_80148624     = 1;
        panel_x        = panel->pos.x;
        initial_cursor = panel->group_cursor;
        initial_first  = panel->group_first;
        D_80148498     = 0;
        D_80148628     = panel_x + 7;
        row_offset     = ((initial_cursor - initial_first) * 0xD) + 0x1B;
        D_8014862A     = panel->pos.y + row_offset;
    }
    buttons = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    if (buttons & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_8014843C = 0x32;
        panel->group--;
        if ((s8)panel->group < 0) {
            panel->group = 3;
        }
    } else if (buttons & PADLright) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_8014843C = 0x31;
        panel->group++;
        if (panel->group >= 4U) {
            panel->group = 0;
        }
    }
    old_cursor = panel->group_cursor;
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            panel->group_cursor = (panel->group_cursor - 1);
        }
        if ((panel->group_cursor) < (panel->group_first)) {
            panel->confirm_gate = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old_cursor < 0x7FU) {
            panel->group_cursor = (panel->group_cursor + 1);
        }
        if ((panel->group_cursor) >= (panel->group_first + 9)) {
            panel->confirm_gate = 0x10;
        }
    } else if (buttons & PADL1) {
        row_limit = panel->group_first & BYTE_MASK;
        if (row_limit == 0) {
            panel->group_cursor = 0U;
        } else if (row_limit < 9U) {
            panel->group_cursor = (panel->group_cursor - panel->group_first);
            panel->group_first  = 0U;
        } else {
            panel->group_cursor = (panel->group_cursor - 9);
            new_row             = panel->group_first - 9;
            panel->group_first  = new_row;
        }
    } else if (buttons & PADR1) {
        row_count = panel->group_first & BYTE_MASK;
        if (row_count == 119) {
            panel->group_cursor = 0x7FU;
        } else if (row_count >= 111U) {
            new_row             = panel->group_cursor + 0x77;
            panel->group_cursor = new_row - panel->group_first;
            panel->group_first  = 0x77;
        } else {
            panel->group_cursor = (panel->group_cursor + 9);
            panel->group_first  = panel->group_first + 9;
        }
    }
    if (old_cursor != panel->group_cursor) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (panel->confirm_gate == 0) {
        if ((g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
            selected_item      = (g_ShopItemId = D_801C893C[panel->group][panel->group_cursor]);
            g_ShopItemCategory = panel->group;
            D_80148628         = panel->pos.x + 7;
            D_8014862A         = panel->pos.y + (((panel->group_cursor - panel->group_first) * ((unsigned long)0xD)) + 0x1B);
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            if (func_801AF494(panel->kind, CHAR_ID_RYU_YOUNG, g_ShopItemCategory, g_ShopItemId) & BYTE_MASK) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                selected_cursor    = panel->group_cursor;
                g_ShopStockIndex   = selected_cursor;
                g_ShopItemCountMax = D_801C8950[g_ShopItemCategory][(s8)selected_cursor];
                g_ShopItemCount    = 1;
                g_ShopItemPrice    = Shop_GetSellPrice(g_ShopItemCategory, g_ShopItemId, D_801E606C);
                counter            = &D_80148652;
                *counter           = *counter + 1;
                return;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            return;
        }
        if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            D_8014842F = 1;
            D_80148654 = 7;
            D_80148652 += 3;
        }
    }
}
