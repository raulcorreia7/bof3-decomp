#include "start_08.h"

MATCH void func_801D5A28(void) {
    s32            buttons;
    u8             count;
    u8             group_index;
    u8             i;
    u8*            choice;
    Character*     record;
    MenuPanelTask* task;
    u8*            group;

    task  = &g_UiPanelTasks[MENU_START_PANEL_CURSOR];
    group = &g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A;
    Menu_DrawClutStrip(g_WindowClut);
    task->active = 1;
    task->pos.vx = g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vx + 6;
    task->pos.vy = (u16)(g_UiPanelTasks[MENU_START_PANEL_ITEMS].pos.vy + (*group * 0xD + 0x57));
    buttons      = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    task         = &g_UiPanelTasks[MENU_START_PANEL_ITEMS];
    task->flags  = 1;
    task->unk_0B = 0xFF;
    if (buttons & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *group += 1;
        if (*group >= EQUIP_SLOT_COUNT) {
            *group = 0;
        }
    } else if (buttons & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        *group -= 1;
        if ((s8)*group < 0) {
            *group = 5;
        }
    }
    count = Party_CountOrder(PARTY_ORDER_FIELD);
    if (buttons & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        task->unk_0C -= 1;
        if ((s8)task->unk_0C < 0) {
            task->unk_0C = count - 1;
        }
    } else if (buttons & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        task->unk_0C += 1;
        if ((s8)count - 1 < task->unk_0C) {
            task->unk_0C = 0;
        }
    }
    g_UiPanelTasks[14].unk_09 = task->unk_0A;
    g_UiPanelTasks[14].unk_0C = task->unk_0C;
    g_UiPanelTasks[14].unk_0A = s_SkillOrderGroups[g_UiPanelTasks[13].unk_0C][g_UiPanelTasks[13].unk_0A];
    record                    = &g_Characters[g_CharSlot[g_PartyFieldOrder[task->unk_0C]]];
    switch (task->unk_0A) {
        case EQUIP_SLOT_WEAPON:
        default:
            group_index = ITEM_CATEGORY_WEAPON;
            choice      = &record->equip.weapon;
            break;
        case EQUIP_SLOT_SHIELD:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = &record->equip.shield;
            break;
        case EQUIP_SLOT_HELMET:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = &record->equip.helmet;
            break;
        case EQUIP_SLOT_ARMOR:
            group_index = ITEM_CATEGORY_ARMOR;
            choice      = &record->equip.armor;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            group_index = ITEM_CATEGORY_ACCESSORY;
            choice      = &record->equip.accessories[0];
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            group_index = ITEM_CATEGORY_ACCESSORY;
            choice      = &record->equip.accessories[1];
            break;
    }
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(group_index, *choice);
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        u8* step;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        g_UiPanelTasks[14].unk_0B = s_SkillOrderTypes[g_UiPanelTasks[13].unk_0C][g_UiPanelTasks[13].unk_0A];
        step                      = &D_80148651;
        g_UiPanelTasks[13].unk_0B = g_UiPanelTasks[13].unk_0A;
        (*step)++;
        return;
    }
    if (g_PadStates[0].pressed & PADRleft) {
        if (task->unk_0A != 0 && *choice != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Item_Add(group_index, *choice, 1, 0);
            *choice = 0;
            Char_RebuildStats(record);
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        g_UiPanelTasks[14].state = 3;
        /* Byte constraint: the three stores below use the absolute cells. */
        task                     = &g_UiPanelTasks[MENU_START_PANEL_ITEMS];
        task->state              = 4;
        task->unk_0B             = 0xFF;
        task->unk_0A             = 0xFF;
        i                        = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_UiPanelTasks[i + 4].state = 8;
            i++;
        }
        g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
        D_80148654                                     = 0;
        D_80148651 -= 2;
    }
}
