#include "start_08.h"

/* Moves the formation cursor over the party slots and swaps the picked pair. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_UpdateFormation(void) {
    s8  old_column;
    s8  old_row;
    s32 cell;
    s32 dx;
    s32 dy;
    s32 i;
    s32 index;
    s32 message;

    dx         = 0;
    dy         = 0;
    old_column = 0;
    Menu_DrawClutStrip(g_WindowClut);
    g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
    if (g_FormationPickColumn != 0x7F) {
        index                                                = (g_FormationPickRow * 3) + g_FormationPickColumn;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].pos.x  = D_801EC4D0[index].unk_00;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 1;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].pos.y  = D_801EC4D0[index].unk_02;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A = D_801EC4D0[index].unk_04 + 1;
    }
    index                     = (g_FormationCursorRow * 3) + g_FormationCursorColumn;
    g_UiPanelTasks[20].pos.x  = D_801EC4D0[index].unk_00;
    g_UiPanelTasks[20].active = 1;
    g_UiPanelTasks[20].pos.y  = D_801EC4D0[index].unk_02;
    g_UiPanelTasks[20].unk_0B = 1;
    g_UiPanelTasks[20].unk_0A = D_801EC4D0[index].unk_04 + 1;
    for (i = 0; i < 6; i++) {
        g_UiPanelTasks[MENU_PANEL_CARD_FIRST + i].unk_0C = 0;
    }
    if (g_FormationCursorColumn == 0) {
        cell = 1 << g_FormationCursorRow;
    } else {
        cell = 7;
    }
    g_UiPanelTasks[(g_FormationRow * 2) + (g_FormationColumn + 0xB)].unk_0C = cell;
    if (g_FormationCursorColumn != 0) {
        message = (g_FormationCursorRow * 2) + (g_FormationCursorColumn + 0x76);
    } else {
        message = 0x3B;
    }
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = message;
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_PadStates[0].pressed) {
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
        if (g_FormationCursorColumn != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
            g_FormationColumn     = g_FormationCursorColumn;
            g_FormationRow        = g_FormationCursorRow;
            D_801ED660            = g_FormationCursorColumn;
            D_801ED664            = g_FormationCursorRow;
        } else if (g_FormationPickColumn == 0x7F) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_FormationPickColumn = g_FormationCursorColumn;
            g_FormationPickRow    = g_FormationCursorRow;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            Menu_SwapBytes4(&g_PartyBattleOrder[g_FormationCursorRow], &g_PartyBattleOrder[g_FormationPickRow]);
            if (g_FormationCursorRow != g_FormationPickRow) {
                D_801ED660 = g_FormationCursorRow;
                D_801ED664 = g_FormationPickRow;
            }
            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
        }
    } else if (g_InputMasks[MENU_INPUT_CANCEL] & g_PadStates[0].pressed) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].active = 0;
        g_UiPanelTasks[20].active                            = 0;
        if (g_FormationPickColumn != 0x7F) {
            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
        } else if (D_80148660 != 1) {
            D_80148654       = 0;
            g_PartyFormation = ((u8)g_FormationRow * 2) + ((u8)g_FormationColumn - 1);
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            for (i = 0; i < 6; i++) {
                if ((g_UiPanelTasks[MENU_PANEL_CARD_FIRST + i].active != 0) && (g_UiPanelTasks[MENU_PANEL_CARD_FIRST + i].mode == 0xB)) {
                    g_UiPanelTasks[MENU_PANEL_CARD_FIRST + i].state = 1;
                }
            }
            D_80148654 = 5;
            g_MenuStep.state += 1;
        } else {
            g_MenuStep.sub_step = 6;
            g_MenuStep.state    = 0;
            D_80148660          = 0;
            g_GameEntrySubstate += 1;
        }
    }
    i = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown));
    if (i & PADLup) {
        dy = -1;
    }
    if (i & PADLdown) {
        dy = 1;
    }
    old_row = g_FormationCursorRow;
    do {
        g_FormationCursorRow += dy;
        if ((s8)g_FormationCursorRow < 0) {
            g_FormationCursorRow = 2;
        }
        if (g_FormationCursorRow >= 3) {
            g_FormationCursorRow = 0;
        }
    } while (g_FormationCells[(g_FormationCursorRow * 3) + g_FormationCursorColumn] == 0);
    if (g_FormationPickColumn != 0) {
        i = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLright | PADLleft));
        if (i & PADLleft) {
            dx = -1;
        }
        if (i & PADLright) {
            dx = 1;
        }
        old_column = g_FormationCursorColumn;
        do {
            g_FormationCursorColumn += dx;
            if ((s8)g_FormationCursorColumn < 0) {
                g_FormationCursorColumn = 2;
            }
            if (g_FormationCursorColumn >= 3) {
                g_FormationCursorColumn = 0;
            }
        } while (g_FormationCells[(g_FormationCursorRow * 3) + g_FormationCursorColumn] == 0);
    }
    if ((old_column != g_FormationCursorColumn) || (old_row != g_FormationCursorRow)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    g_PartyFormation = ((u8)g_FormationColumn + ((u8)g_FormationRow * 2)) - 1;
}
#else
INCLUDE_ASM(Menu_UpdateFormation);
#endif
