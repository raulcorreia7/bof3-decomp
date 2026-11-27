#include "start_08.h"

/* Moves the formation cursor over the party slots and swaps the picked pair. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_UpdateFormation(void) {
    volatile u8* frame;
    s32          index;
    s8           dx;
    s8           dy;
    s8           old_column;
    u8           old_row;
    s8           i;
    s32          input;
    s32          message;
    u16          y;

    dx         = 0;
    dy         = 0;
    old_column = 0;
    Menu_DrawClutStrip(g_WindowClut);
    frame  = &D_801485DC;
    *frame = 0;
    if (g_FormationPickColumn != 0x7F) {
        s32 pick;
        u16 y2;

        pick                                                 = g_FormationPickRow * 3 + g_FormationPickColumn;
        D_801485E0                                           = D_801EC4D0[pick].unk_00;
        y2                                                   = D_801EC4D0[pick].unk_02;
        *frame                                               = 1;
        D_801485E2                                           = y2;
        g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A = D_801EC4D0[pick].unk_04 + 1;
        g_UIPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
    }
    index                     = g_FormationCursorRow * 3 + g_FormationCursorColumn;
    g_UIPanelTasks[20].pos.vx = D_801EC4D0[index].unk_00;
    y                         = D_801EC4D0[index].unk_02;
    frame[0x24]               = 1;
    g_UIPanelTasks[20].pos.vy = y;
    g_UIPanelTasks[20].unk_0A = D_801EC4D0[index].unk_04 + 1;
    g_UIPanelTasks[20].unk_0B = 1;
    for (i = 0; i < 6; i++) {
        g_UIPanelTasks[MENU_PANEL_CARD_FIRST + i].unk_0C = 0;
    }
    g_UIPanelTasks[g_FormationRow * 2 + (g_FormationColumn + 0xB)].unk_0C = g_FormationCursorColumn == 0 ? 1 << g_FormationCursorRow : 7;
    if (g_FormationCursorColumn != 0) {
        message = g_FormationCursorRow * 2 + (g_FormationCursorColumn + 0x76);
    } else {
        message = 0x3B;
    }
    D_801484CC = message;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        D_801485DC = 0;
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
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        volatile u8* closed;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        closed     = &D_801485DC;
        *closed    = 0;
        D_80148600 = 0;
        if (g_FormationPickColumn != 0x7F) {
            s32 pick;
            u16 y2;

            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
        } else if (D_80148660 != 1) {
            MenuPanelTask* card;

            D_80148654       = 0;
            g_PartyFormation = (u8)g_FormationRow * 2 + ((u8)g_FormationColumn - 1);
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            for (i = 0; i < 6; i++) {
                card = &((MenuPanelTask*)(closed - 0xFC))[i];
                if (card->active != 0 && card->mode == 0xB) {
                    card->state = 1;
                }
            }
            D_80148654 = 5;
            D_80148652 += 1;
        } else {
            D_80148651 = 6;
            D_80148652 = 0;
            D_80148660 = 0;
            g_GameEntrySubstate += 1;
        }
    }
    input = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown));
    if (input & PADLup) {
        dy = -1;
    }
    if (input & PADLdown) {
        dy = 1;
    }
    old_row = g_FormationCursorRow;
    do {
        g_FormationCursorRow += dy;
        if (g_FormationCursorRow < 0) {
            g_FormationCursorRow = 2;
        }
        if (g_FormationCursorRow >= 3) {
            g_FormationCursorRow = 0;
        }
    } while (g_FormationCells[g_FormationCursorRow][g_FormationCursorColumn] == 0);
    if (g_FormationPickColumn != 0) {
        input = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLright | PADLleft));
        if (input & PADLleft) {
            dx = -1;
        }
        if (input & PADLright) {
            dx = 1;
        }
        old_column = g_FormationCursorColumn;
        do {
            g_FormationCursorColumn += dx;
            if (g_FormationCursorColumn < 0) {
                g_FormationCursorColumn = 2;
            }
            if (g_FormationCursorColumn >= 3) {
                g_FormationCursorColumn = 0;
            }
        } while (g_FormationCells[g_FormationCursorRow][g_FormationCursorColumn] == 0);
    }
    if (old_column != g_FormationCursorColumn || (s8)old_row != g_FormationCursorRow) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    g_PartyFormation = (u8)g_FormationColumn + (u8)g_FormationRow * 2 - 1;
}
#else
INCLUDE_ASM(Menu_UpdateFormation);
#endif
