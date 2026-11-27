#include "start_08.h"

/* Runs the four-row choice menu: moves the D_801ED618 cursor on up/down, then on confirm advances the menu step by
 * the chosen row, or on cancel backs out to the previous panel. */
MATCH void func_801D2EAC(void) {
    s32 pad;
    u8  cursor;

    Menu_DrawClutStrip(g_WindowClut);
    D_80148504.type                                           = 0;
    D_80148504.group_cursor                                   = 0xFF;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UIPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B          = 0xFF;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801ED618 + 0x13;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = g_UIPanelTasks[MENU_START_PANEL_COMMANDS].pos.vx + D_801ED618 * 0x30;
    g_UIPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = g_UIPanelTasks[MENU_START_PANEL_COMMANDS].pos.vy + 4;
    pad                                                       = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLright | PADLleft));
    cursor                                                    = D_801ED618;
    if (pad & PADLleft) {
        D_801ED618--;
        if (D_801ED618 < 0) {
            D_801ED618 = 3;
        }
    }
    if (pad & PADLright) {
        D_801ED618++;
        if (D_801ED618 >= 4) {
            D_801ED618 = 0;
        }
    }
    if ((s8)cursor != D_801ED618) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        g_UIPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B = D_801ED618;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        if (D_801ED618 == 1) {
            u8* step = &D_80148651;

            D_80148652 = 0;
            *step += 3;
            return;
        }
        if (D_801ED618 == 3) {
            u8* step = &D_80148651;

            D_80148504.group        = 4;
            D_80148504.group_first  = s_ChoiceMenuValues[4];
            D_80148504.group_cursor = s_ChoiceMenuCursors[4];
            *step += 7;
            return;
        }
        {
            u8* step  = &D_80148651;
            s32 group = D_80148504.group;
            s32 group_cursor;
            u8  next;

            next                   = *step;
            D_80148504.group_first = s_ChoiceMenuValues[group];
            group_cursor           = s_ChoiceMenuCursors[group];
            next += 1;
            D_80148504.drawn_cursor = 0xFF;
            *step                   = next;
            D_80148504.group_cursor = group_cursor;
            return;
        }
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].state = 1;
        g_UIPanelTasks[MENU_START_PANEL_COMMANDS].state    = 1;
        g_UIPanelTasks[MENU_START_PANEL_ITEMS].state       = 1;
        g_UIPanelTasks[MENU_START_PANEL_CURSOR].active     = 0;
        {
            u8* value = &D_80148654;

            *value += 5;
        }
        D_80148651 += 2;
    }
}
