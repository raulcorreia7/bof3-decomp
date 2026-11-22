#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D55B0(void) {
    s32            pressed;
    u8             count;
    u8             old;
    u8             i;
    u8*            party_cursor;
    u8*            sel;
    MenuPanelTask* cursor_task;

    party_cursor = &D_80148654 + 2;
    cursor_task  = &g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME];
    Menu_DrawClutStrip(D_80144953);
    cursor_task->active = 1;
    cursor_task->pos.x  = g_UiPanelTasks[4].pos.x;
    sel                 = &cursor_task[MENU_START_PANEL_ITEMS - MENU_START_PANEL_CURSOR_FRAME].unk_0C;
    cursor_task->pos.y  = *sel * 0x36 + 0x3E;
    pressed             = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    old                 = *sel;
    count               = Party_CountOrder(PARTY_ORDER_FIELD);
    if (pressed & PADLup) {
        *sel -= 1;
        if ((s8)*sel < 0) {
            *sel = count - 1;
        }
    } else if (pressed & PADLdown) {
        *sel += 1;
        if (*sel > count - 1) {
            *sel = 0;
        }
    }
    if ((s8)old != *sel) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }

    if ((s8)D_801ED620 == 1) {
        Menu_PreviewStrongestEquipment(*sel);
    }
    if ((s8)D_801ED620 == 2) {
        func_801D6AC4(*sel);
    }

    UI_MessageSetVariable(0, 5, g_Characters[g_CharSlot[g_PartyFieldOrder[D_80148510]]].name);
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801EC448[(s8)D_801ED620];
    g_UiPanelTasks[MENU_START_PANEL_ITEMS].flags              = (u8)D_801EC450[(s8)D_801ED620];
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        if ((s8)D_801ED620 == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                g_UiPanelTasks[i + 4].state = 7;
            }
            cursor_task->active                           = 0;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].state  = 3;
            g_UiPanelTasks[14].panel                      = 6;
            g_UiPanelTasks[14].mode                       = 0x12;
            g_UiPanelTasks[14].state                      = 4;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0xFF;
            g_UiPanelTasks[14].active                     = 1;
            g_UiPanelTasks[14].pos.x                      = 320;
            g_UiPanelTasks[14].pos.y                      = 62;
            g_UiPanelTasks[14].unk_0B                     = 0xFF;
            g_UiPanelTasks[14].unk_0C                     = *sel;
            g_UiPanelTasks[14].unk_08                     = 0;
            g_UiPanelTasks[14].flags                      = 0;
            g_UiPanelTasks[14].unk_09                     = 0;
            g_UiPanelTasks[14].u.addr.unk_10              = 0;
            *party_cursor                                 = *sel;
            D_80148654                                    = 5;
            g_MenuStep.sub_step += 1;
            g_UiPanelTasks[14].unk_0A = s_SkillOrderGroups[*sel][0];
        } else if ((s8)D_801ED620 == 3) {
            g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0A        = 1;
            g_UiPanelTasks[MENU_START_PANEL_ITEMS].unk_0B        = 0xFF;
            g_MenuStep.sub_step += 5;
        } else {
            func_801D6E6C();
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        cursor_task->active = 0;
        D_80148654          = 0;
        D_80148663          = *party_cursor;
        g_MenuStep.sub_step -= 1;
    }
}
#else
INCLUDE_ASM(func_801D55B0);
#endif
