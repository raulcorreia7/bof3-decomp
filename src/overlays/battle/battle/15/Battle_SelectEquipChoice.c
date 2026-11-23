#include "battle_15.h"

/* Runs the equipment choice list: moves the cursor by row or page, shows the item description and applies or cancels the choice. */
MATCH void Battle_SelectEquipChoice(void) {
    u16*           pad_state;
    MenuPanelTask* panel;
    s32            buttons;
    u8             old_cursor;
    u8             item_id;
    u8             first_row;
    u8             last_row;
    u8             next;

    if (g_UiPanelTasks[17].state == 0) {
        g_UiPanelTasks[19].active = 1;
        g_UiPanelTasks[19].pos.x  = g_UiPanelTasks[17].pos.x + 7;
        g_UiPanelTasks[19].pos.y  = g_UiPanelTasks[17].pos.y + ((g_UiPanelTasks[17].unk_0B - g_UiPanelTasks[17].unk_0A) * 13 + 26);
    } else {
        g_UiPanelTasks[19].active = 0;
    }
    pad_state = &g_PadStates[0].pressed;
    INPUT_REPEATED(*pad_state, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    panel      = &g_UiPanelTasks[17];
    buttons    = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    old_cursor = g_UiPanelTasks[17].unk_0B;
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            g_UiPanelTasks[17].unk_0B = old_cursor - 1;
        }
        if (g_UiPanelTasks[17].unk_0B < g_UiPanelTasks[17].unk_0A) {
            g_UiPanelTasks[17].u.addr.unk_10 = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old_cursor < 0x7F) {
            g_UiPanelTasks[17].unk_0B = old_cursor + 1;
        }
        if (g_UiPanelTasks[17].unk_0B >= g_UiPanelTasks[17].unk_0A + 7) {
            g_UiPanelTasks[17].u.addr.unk_10 = 0x10;
        }
    } else if (buttons & PADL1) {
        first_row = g_UiPanelTasks[17].unk_0A;
        if (first_row == 0) {
            g_UiPanelTasks[17].unk_0B = 0;
        } else if (first_row < 7) {
            g_UiPanelTasks[17].unk_0B = old_cursor - first_row;
            g_UiPanelTasks[17].unk_0A = 0;
        } else {
            g_UiPanelTasks[17].unk_0B = old_cursor - 7;
            g_UiPanelTasks[17].unk_0A = first_row - 7;
        }
    } else if (buttons & PADR1) {
        last_row = g_UiPanelTasks[17].unk_0A;
        if (last_row == 0x79) {
            g_UiPanelTasks[17].unk_0B = 0x7F;
        } else if (last_row >= 0x73) {
            next                      = old_cursor + 0x79;
            g_UiPanelTasks[17].unk_0B = next - last_row;
            g_UiPanelTasks[17].unk_0A = 0x79;
        } else {
            g_UiPanelTasks[17].unk_0B = old_cursor + 7;
            g_UiPanelTasks[17].unk_0A = last_row + 7;
        }
    }
    if (old_cursor != panel->unk_0B) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    item_id                                         = g_UiPanelTasks[17].flags;
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(Item_GetDescription(g_UiPanelTasks[17].unk_08, item_id) & 0xFFFF);
    pad_state                                       = &g_PadStates[0].pressed;
    if (*pad_state & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        goto equip_exit; /* cancel and a confirmed choice share the panel exit */
    }
    Battle_PreviewEquipment();
    if (*pad_state & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (item_id != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Battle_ApplyEquipment();
        equip_exit:
            g_UiPanelTasks[17].unk_0B = 0xFF;
            g_UiPanelTasks[18].unk_0B = 0xFF;
            g_UiPanelTasks[18].flags  = 1;
            g_Battle.ui_mode -= 1;
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
    }
}
