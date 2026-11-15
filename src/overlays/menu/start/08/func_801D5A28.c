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

    task  = &g_MenuPanelTasks[MENU_START_PANEL_CURSOR];
    group = &g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A;
    Menu_DrawClutStrip(D_80144953);
    task->active = 1;
    task->pos.x  = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.x + 6;
    task->pos.y  = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y + (*group * 0xD + 0x57);
    buttons      = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    task         = &g_MenuPanelTasks[MENU_START_PANEL_ITEMS];
    task->flags  = 1;
    task->unk_0B = 0xFF;
    if (buttons & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        *group += 1;
        if (*group >= EQUIP_SLOT_COUNT) {
            *group = 0;
        }
    } else if (buttons & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        *group -= 1;
        if ((s8)*group < 0) {
            *group = 5;
        }
    }
    count = Party_CountOrder(PARTY_ORDER_FIELD);
    if (buttons & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        task->unk_0C -= 1;
        if ((s8)task->unk_0C < 0) {
            task->unk_0C = count - 1;
        }
    } else if (buttons & PADLright) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        task->unk_0C += 1;
        if ((s8)count - 1 < task->unk_0C) {
            task->unk_0C = 0;
        }
    }
    D_80148531 = task->unk_0A;
    D_80148534 = task->unk_0C;
    D_80148532 = s_SkillOrderGroups[D_80148510][D_8014850E];
    record     = &g_Characters[g_CharSlot[g_PartyFieldOrder[task->unk_0C]]];
    switch (task->unk_0A) {
        case EQUIP_SLOT_WEAPON:
        default:
            group_index = ITEM_CAT_WEAPON;
            choice      = &record->equip.weapon;
            break;
        case EQUIP_SLOT_SHIELD:
            group_index = ITEM_CAT_ARMOR;
            choice      = &record->equip.shield;
            break;
        case EQUIP_SLOT_HELMET:
            group_index = ITEM_CAT_ARMOR;
            choice      = &record->equip.helmet;
            break;
        case EQUIP_SLOT_ARMOR:
            group_index = ITEM_CAT_ARMOR;
            choice      = &record->equip.armor;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            group_index = ITEM_CAT_ACCESSORY;
            choice      = &record->equip.accessories[0];
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            group_index = ITEM_CAT_ACCESSORY;
            choice      = &record->equip.accessories[1];
            break;
    }
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = Item_GetDescription(group_index, *choice);
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        u8* step;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        D_80148533 = s_SkillOrderKinds[D_80148510][D_8014850E];
        step       = &D_80148651;
        D_8014850F = D_8014850E;
        (*step)++;
        return;
    }
    if (g_InputPressed & PADRleft) {
        if (task->unk_0A != 0 && *choice != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            Item_Add(group_index, *choice, 1, 0);
            *choice = 0;
            Char_RebuildStats(record);
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_8014852B   = 3;
        /* Byte constraint: the three stores below use the absolute cells. */
        task         = &g_MenuPanelTasks[MENU_START_PANEL_ITEMS];
        task->state  = 4;
        task->unk_0B = 0xFF;
        task->unk_0A = 0xFF;
        i            = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            g_MenuPanelTasks[i + 4].state = 8;
            i++;
        }
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
        D_80148654                                       = 0;
        D_80148651 -= 2;
    }
}
