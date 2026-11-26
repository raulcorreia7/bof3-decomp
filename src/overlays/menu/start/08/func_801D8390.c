#include "start_08.h"

extern u8 D_80148656;

MATCH void func_801D8390(void) {
    u16*           message;
    MenuPanelTask* list;
    MenuPanelTask* frame;
    s32            pad;
    u8             count;

    Menu_DrawClutStrip(g_WindowClut);
    message                                              = &g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id;
    frame                                                = &g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME];
    *message                                             = 0x17;
    frame->active                                        = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active       = 1;
    frame->pos.vx                                        = g_UiPanelTasks[4].pos.vx;
    frame->pos.vy                                        = g_UiPanelTasks[4].pos.vy + g_UiPanelTasks[16].unk_0A * 0x36;
    D_80148628                                           = D_80148574 + 0x2A;
    D_8014862A                                           = D_80148576 + 7;
    list                                                 = &g_UiPanelTasks[16];
    pad                                                  = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL);
    g_UiPanelTasks[16].flags                             = 0xFF;
    count                                                = Party_CountOrder(PARTY_ORDER_FIELD);
    if (pad & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[16].unk_0A--;
        if ((s8)g_UiPanelTasks[16].unk_0A < 0) {
            g_UiPanelTasks[16].unk_0A = count - 1;
        }
    } else if (pad & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[16].unk_0A++;
        if (count - 1 < g_UiPanelTasks[16].unk_0A) {
            g_UiPanelTasks[16].unk_0A = 0;
        }
    }
    if (pad & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        list->unk_09 = 0x32;
        list->unk_0B--;
        if ((s8)list->unk_0B < 0) {
            list->unk_0B = 3;
        }
    } else if (pad & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        list->unk_09 = 0x31;
        list->unk_0B++;
        if ((u8)list->unk_0B >= 4) {
            list->unk_0B = 0;
        }
    }
    D_80148656 = list->unk_0A;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        frame         = &g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME];
        frame->active = 0;
        D_801485B9    = 6;
        D_801485BA    = 0xF;
        /* Stepping the pointer keeps panel 18 relative to panel 19 (sb -36). */
        frame -= 1;
        frame->active             = 1;
        g_UiPanelTasks[18].pos.vx = 0x28;
        g_UiPanelTasks[18].pos.vy = 0x3C;
        g_BattleEquipSlot         = (g_UiPanelTasks[16].unk_0B == 3) ? 6 : 5;
        g_UiPanelTasks[18].unk_0B = 0;
        D_80148652++;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
        D_80148651 -= 5;
    }
}
