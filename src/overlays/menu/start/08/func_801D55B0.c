#include "start_08.h"

/* Moves the start menu's party-member cursor and opens the chosen command for that member. */
MATCH void func_801D55B0(void) {
    MenuPanelTask* task;
    u8*            sel;
    MenuPanelTask* frame;
    s32            pressed;
    u8             count;
    u8             old;
    u8             i;

    task = &g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME];
    Menu_DrawClutStrip(g_WindowClut);
    task->active                                         = 1;
    sel                                                  = &g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].pos.vx = g_UIPanelTasks[4].pos.vx;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].pos.vy = *sel * 0x36 + 0x3E;
    pressed                                              = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    task                                                 = &g_UIPanelTasks[MENU_START_PANEL_ITEMS];
    old                                                  = *sel;
    count                                                = Party_CountOrder(PARTY_ORDER_FIELD);
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
    if ((s8)old != task->unk_0C) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if ((s8)D_801ED620 == 1) {
        Menu_PreviewStrongestEquipment(task->unk_0C);
    }
    if ((s8)D_801ED620 == 2) {
        func_801D6AC4(task->unk_0C);
    }
    UI_MessageSetVariable(0, 5, g_Characters[g_CharSlot[g_PartyFieldOrder[g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]]].name);
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801EC448[(s8)D_801ED620];
    g_UIPanelTasks[MENU_START_PANEL_ITEMS].flags              = (u8)D_801EC450[(s8)D_801ED620];
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        if (LOB(D_801ED620) == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                g_UIPanelTasks[i + 4].state = 7;
            }
            frame                                         = &g_CursorFramePanel;
            frame->active                                 = 0;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A = 0;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].state  = 3;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0xFF;
            g_UIPanelTasks[14].panel                      = 6;
            g_UIPanelTasks[14].mode                       = 0x12;
            g_UIPanelTasks[14].state                      = 4;
            frame -= 5;
            frame->active                    = 1;
            g_UIPanelTasks[14].pos.vx        = 320;
            g_UIPanelTasks[14].pos.vy        = 62;
            g_UIPanelTasks[14].unk_0B        = 0xFF;
            g_UIPanelTasks[14].unk_0C        = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C;
            g_UIPanelTasks[14].unk_0A        = s_SkillOrderGroups[g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C][0];
            g_UIPanelTasks[14].unk_08        = 0;
            g_UIPanelTasks[14].flags         = 0;
            g_UIPanelTasks[14].unk_09        = 0;
            g_UIPanelTasks[14].u.addr.unk_10 = 0;
            g_PartyCursor                    = g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0C;
            D_80148654                       = 5;
            D_80148651++;
        } else if (LOB(D_801ED620) == 3) {
            g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0A        = 1;
            g_UIPanelTasks[MENU_START_PANEL_ITEMS].unk_0B        = 0xFF;
            g_MenuStep.sub_step += 5;
        } else {
            func_801D6E6C();
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
        D_80148654                                           = 0;
        D_80148663                                           = g_PartyCursor;
        D_80148651 -= 1;
    }
}
