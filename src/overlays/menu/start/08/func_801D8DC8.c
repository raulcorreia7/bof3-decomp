#include "start_08.h"

/* The scrolling list: eighteen entries, nine rows on screen, each row one cell tall. unk_0A is the first row on
 * screen, unk_0B the cursor entry and unk_08 the scroll step the panel animation applies. */
#define START_LIST_LAST_ENTRY     17
#define START_LIST_VISIBLE_ROWS   9
#define START_LIST_ROW_HEIGHT     13
#define START_LIST_FIRST_ROW_Y    26
#define START_LIST_CURSOR_X       7
#define START_LIST_SCROLL_UP      0xF0
#define START_LIST_SCROLL_DOWN    0x10

/* The base of the message ids of the marked entry's description (panel 11 unk_10). */
#define START_LIST_DESCRIPTION_ID 0x4183

MATCH void func_801D8DC8(void) {
    MenuPanelTask* panel;
    s32            buttons;
    u8             old;
    u8             column;
    s32            next;

    Menu_DrawClutStrip(D_80144953);
    panel = &g_MenuPanelTasks[17];
    if (D_801485A0 != 0) {
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = D_801485A0 + START_LIST_DESCRIPTION_ID;
    } else {
        g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    }
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = panel->pos.x + START_LIST_CURSOR_X;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y =
        panel->pos.y + ((panel->unk_0B - panel->unk_0A) * START_LIST_ROW_HEIGHT + START_LIST_FIRST_ROW_Y);
    buttons = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
    old     = panel->unk_0B;
    if (buttons & PADLup) {
        if (old != 0) {
            panel->unk_0B = old - 1;
        }
        if (panel->unk_0B < panel->unk_0A) {
            panel->unk_08 = START_LIST_SCROLL_UP;
        }
    } else if (buttons & PADLdown) {
        if (old < START_LIST_LAST_ENTRY) {
            panel->unk_0B = old + 1;
        }
        if (panel->unk_0B >= panel->unk_0A + START_LIST_VISIBLE_ROWS) {
            panel->unk_08 = START_LIST_SCROLL_DOWN;
        }
    } else if (buttons & PADL1) {
        column = panel->unk_0A;
        if (column == 0) {
            panel->unk_0B = 0;
        } else if (column < START_LIST_VISIBLE_ROWS) {
            panel->unk_0B = old - column;
            panel->unk_0A = 0;
        } else {
            panel->unk_0B = old - START_LIST_VISIBLE_ROWS;
            panel->unk_0A = panel->unk_0A - START_LIST_VISIBLE_ROWS;
        }
    } else if (buttons & PADR1) {
        if (panel->unk_0A == START_LIST_VISIBLE_ROWS) {
            panel->unk_0B = START_LIST_LAST_ENTRY;
        } else if (panel->unk_0A != 0) {
            next          = old + START_LIST_VISIBLE_ROWS;
            panel->unk_0B = next - panel->unk_0A;
            panel->unk_0A = START_LIST_VISIBLE_ROWS;
        } else {
            panel->unk_0B = old + START_LIST_VISIBLE_ROWS;
            panel->unk_0A = panel->unk_0A + START_LIST_VISIBLE_ROWS;
        }
    }
    D_801ED891 = g_BattleListCursor;
    D_801ED890 = g_MenuPanelTasks[17].unk_0A;
    if (old != panel->unk_0B) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_80148597                                       = 1;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
        D_80148654                                       = 7;
        D_80148652 += 1;
    }
}
