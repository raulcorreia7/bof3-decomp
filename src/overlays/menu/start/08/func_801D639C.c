#include "start_08.h"

MATCH void func_801D639C(void) {
    s32 input;
    s32 slot_flag;
    s32 group_index;
    s32 one;
    u8* choice;
    u8* record;
    u8  next_slot;
    u8  prev_slot;

    choice = &g_WindowClut;
    Menu_DrawClutStrip(*choice);
    choice += 0x15;
    record = (g_CharSlot[g_PartyFieldOrder[g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]] * 0xA4) + choice;
    switch (g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A) {
        case EQUIP_SLOT_WEAPON:
        default:
            group_index = ITEM_CATEGORY_WEAPON;
            choice      = record + 0xE;
            break;
        case EQUIP_SLOT_SHIELD:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = record + 0xF;
            break;
        case EQUIP_SLOT_HELMET:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = record + 0x10;
            break;
        case EQUIP_SLOT_ARMOR:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = record + 0x11;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            group_index = ITEM_CATEGORY_ACCESSORY;
            choice      = record + 0x12;
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            group_index = ITEM_CATEGORY_ACCESSORY;
            choice      = record + 0x13;
            break;
    }
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(group_index, *choice);
    one                                                       = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = (u16)g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 6;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = (u16)(g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + (g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A * 0xD + 0x57));
    input                                                     = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    if (input & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        next_slot                                     = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A + 1;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = next_slot;
        if ((u32)(next_slot & BYTE_MASK) >= 6U) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 1;
        }
    } else if (input & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        prev_slot                                     = g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A - 1;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = prev_slot;
        if (!(prev_slot & BYTE_MASK)) {
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 5;
        }
    }
    slot_flag = func_801D70EC() & BYTE_MASK;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (slot_flag != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Item_Add(group_index, *choice, 1, 0);
            *choice = 0;
            Char_RebuildStats((Character*)record);
            func_801D6E6C();
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 1;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active       = 0;
        g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A        = 0xFF;
        D_80148654                                           = 0;
        D_80148651 -= 5;
    }
}
