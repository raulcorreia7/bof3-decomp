#include "commu01_07.h"
#include "overlays/commu/shared/Commu_CursorTriangle.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The scene entry: the commu step byte selects the step handler. */
/* func_801D0C2C */
MATCH void Fairy_Commu01Run(void) {
    SYS_DISPATCH_BYTE(g_Commu01Steps, D_801F294C);
}

/* Puts the cell cursor on the idle fairies and shows the overview message. */
/* func_801D0C68 */
MATCH void Fairy_Commu01Start(void) {
    g_FairyCursorColumn  = 1;
    g_FairyCursorGridRow = 0;
    g_FairyCursorZone    = FAIRY_CURSOR_IDLE;
    g_FairyMessage       = 181;
    D_801F294C++;
}

/* Confirms the selected cell, or moves the cell cursor. */
/* func_801D0CAC */
MATCH void Fairy_Commu01PickCell(void) {
    u16 pad;
    u8* counter;
    u8  mode;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        counter        = (u8*)&g_SceneEventState.step;
        g_FairyMessage = 0xFFFF;
        *counter += 1;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        D_801F294D                = 0;
        g_FairyJobOrdinal         = 0;
        g_FairySavedCursorColumn  = g_FairyCursorColumn;
        g_FairySavedCursorGridRow = g_FairyCursorGridRow;
        mode                      = g_FairyCursorZone;
        g_FairySavedCursorZone    = mode;
        switch (mode) {
            case FAIRY_CURSOR_IDLE:
            case FAIRY_CURSOR_JOBS:
                if (Fairy_GetJobActive(g_SceneEventState.selection) != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                    Fairy_ShowTypeMessage();
                    D_801F294C++;
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case FAIRY_CURSOR_ROOMS:
                if (D_801F286D[g_GameAreaId] < g_SceneEventState.selection) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                    Fairy_ShowTypeMessage();
                    D_801F294C++;
                }
                break;
            default:
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                break;
        }
    } else {
        Fairy_MoveCursor(&g_SceneEventState.selection);
    }
    Fairy_DrawOverview();
    Fairy_DrawCellFrame(g_SceneEventState.selection, 0);
}

/* Runs the handler the saved cursor zone selects. */
/* func_801D0E44 */
MATCH void Fairy_Commu01DispatchMode(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Steps, g_FairySavedCursorZone);
}

/* Runs the move handler the sub-step selects. */
/* func_801D0E80 */
MATCH void Fairy_Commu01DispatchMove(void) {
    SYS_DISPATCH_BYTE(g_Commu01MoveSteps, D_801F294D);
}

/* Moves the cursor among the active jobs of the selected job type and draws the job box. */
/* func_801D0EBC */
MATCH void Fairy_Commu01PickJob(void) {
    u16  pad;
    u16* pad_word;
    s32  direction;
    u8   count;
    u8   ordinal;
    u8*  row;
    s32  x;
    s32  y;
    s32  offset;
    s8   col;
    s8   line;

    pad_word = &g_PadStates[0].pressed;
    pad      = *pad_word;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_FairyMessage = 0xB5;
        D_801F294C--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_FairyMessage = 0x44;
        D_801D4E28     = g_SceneEventState.selection;
        D_801F294D++;
    } else {
        count     = Fairy_GetJobActive(g_SceneEventState.selection);
        direction = INPUT_REPEATED(*pad_word, (PADLleft | PADLright));
        ordinal   = g_FairyJobOrdinal;
        if (direction & PADLright) {
            g_FairyJobOrdinal = ordinal + 1;
            if ((s8)(ordinal + 1) == count) {
                g_FairyJobOrdinal = 0;
            }
        } else if (direction & PADLleft) {
            g_FairyJobOrdinal = ordinal - 1;
            if ((s8)(ordinal - 1) < 0) {
                g_FairyJobOrdinal = count - 1;
            }
        }
        if (ordinal != g_FairyJobOrdinal) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }
    Fairy_DrawOverview();
    row = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*row, 1);
    if (*row == 0) {
        ordinal = g_FairyJobOrdinal;
        offset  = ((s32)ordinal << 24) >> 21;
        Fairy_DrawCursor(offset + 0x28, 0x39, 0);
        Fairy_DrawChannelBox(offset + 0x30, 0x42, Fairy_FindJob(*row, g_FairyJobOrdinal), 0);
    } else {
        col  = (s8)g_FairyJobOrdinal % 5;
        line = (s8)g_FairyJobOrdinal / 5;
        x    = col * 8;
        y    = (*row - FAIRY_JOB_HUNT) * 54 + line * 7;
        Fairy_DrawCursor(x + 0xFA, (s16)(y + 0x44), 0);
        Fairy_DrawChannelBox(x + 0xA8, (s16)(y + 0x4C), Fairy_FindJob(*row, g_FairyJobOrdinal), 0);
    }
}

/* Moves the target of the job's move or commits it, then draws both cells. */
/* func_801D1158 */
MATCH void Fairy_Commu01PickTarget(void) {
    u16 pad;
    s32 committed;
    u8* row;
    s32 y;
    s8  col;
    s8  line;
    s32 line_inset;

    pad       = g_PadStates[0].pressed;
    committed = 0;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        Fairy_ShowTypeMessage();
        Fairy_RestoreCursor();
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        committed = Fairy_MoveJob(0);
        if (committed & BYTE_MASK) {
            g_FairyMessage = 0xB5;
        }
    } else {
        row = &D_801D4E28;
        Fairy_MoveCursor(row);
        Fairy_ShowTargetMessage(row);
    }
    Fairy_DrawOverview();
    row = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*row, 1);
    Fairy_DrawCellFrame(D_801D4E28, 0);
    if ((committed & BYTE_MASK) == 0) {
        if (*row == 0) {
            Fairy_DrawCursor((s8)g_FairyJobOrdinal * 8 + 0x28, 0x39, 1);
        } else {
            line_inset = 0x44;
            col        = (s8)g_FairyJobOrdinal % 5;
            line       = (s8)g_FairyJobOrdinal / 5;
            y          = (*row - FAIRY_JOB_HUNT) * 54 + (line * 7 + line_inset);
            Fairy_DrawCursor(col * 8 + 0xFA, (s16)y, 1);
        }
        Fairy_DrawChannelBox(0xA0, 0x3E, Fairy_FindJob(g_SceneEventState.selection, g_FairyJobOrdinal), 1);
    }
}

/* Runs the room handler the sub-step selects. */
/* func_801D1328 */
MATCH void Fairy_Commu01DispatchRoom(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Sub1Steps, D_801F294D);
}

/* Moves the cursor among a room and its jobs; confirming a job starts its move, confirming the room opens its type list. */
/* func_801D1364 */
MATCH void Fairy_Commu01PickRoomJob(void) {
    s16 x;
    s16 y;
    u8* selection;
    u8  old_row;
    s8  row;
    u8  count;
    s32 room;
    u16 buttons;

    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_FairyMessage = 181;
        D_801F294C--;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        row = g_FairyJobOrdinal;
        if (row != 0) {
            g_FairyMessage = 68;
            D_801D4E28     = g_SceneEventState.selection;
            D_801F294D++;
        } else {
            room = g_SceneEventState.selection - 1;
            if (g_FairyRooms[room * 8] == 0) {
                D_801D4E28 = 0;
            } else {
                D_801D4E28 = g_FairyRooms[room * 8] - 4;
            }
            D_801D4E1C = 0xFF;
            D_801D4E20 = 0xFF;
            D_801D4E2C = 0;
            D_801D4E30 = 0;
            D_801F294D = 2;
        }
    } else {
        buttons = INPUT_REPEATED(g_PadStates[0].pressed, (PADLright | PADLleft));
        old_row = g_FairyJobOrdinal;
        count   = Fairy_GetJobActive(g_SceneEventState.selection);
        if (buttons & PADLleft) {
            g_FairyJobOrdinal--;
            if ((s8)g_FairyJobOrdinal < 0) {
                g_FairyJobOrdinal = count;
            }
        } else if (buttons & PADLright) {
            g_FairyJobOrdinal++;
            if ((count & BYTE_MASK) < (s8)g_FairyJobOrdinal) {
                g_FairyJobOrdinal = 0;
            }
        }
        if (old_row != g_FairyJobOrdinal) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }

    Fairy_DrawOverview();
    selection = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*selection, 1);
    Fairy_GetJobPos(&x, &y, *selection, g_FairyJobOrdinal);
    row = g_FairyJobOrdinal;
    if (row == 0) {
        Fairy_DrawCursor((s16)x, y, 0);
    } else {
        Fairy_DrawCursor((s16)(x + 4), y, 0);
        Fairy_DrawChannelBox((s16)(x + 0x10), (s16)(y - 8), Fairy_FindJob(*selection, (g_FairyJobOrdinal - 1) & BYTE_MASK) & BYTE_MASK, 0);
    }
}

/* Moves the target job type of a room job and commits the move, then draws both cells. */
/* func_801D1630 */
MATCH void Fairy_Commu01PickRoomTarget(void) {
    u16 x;
    s16 y;
    s32 result;
    u8* selection;

    result = 0;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        Fairy_RestoreCursor();
        Fairy_ShowTypeMessage();
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        result = Fairy_MoveJob(1);
        if (result & BYTE_MASK) {
            g_FairyMessage = 181;
        }
    } else {
        Fairy_MoveCursor(&D_801D4E28);
        Fairy_ShowTargetMessage(&D_801D4E28);
    }
    Fairy_DrawOverview();
    selection = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*selection, 1);
    Fairy_DrawCellFrame(D_801D4E28, 0);
    if (!(result & BYTE_MASK)) {
        Fairy_GetJobPos(&x, &y, *selection, g_FairyJobOrdinal);
        Fairy_DrawCursor((s16)(x + 4), y, 1);
        Fairy_DrawChannelBox(0xA0, 0x3E, Fairy_FindJob(*selection, (g_FairyJobOrdinal - 1) & BYTE_MASK) & BYTE_MASK, 1);
    }
}

/* Moves the cursor in the room type list and draws the list. */
/* func_801D1778 */
MATCH void Fairy_Commu01PickRoomType(void) {
    u16 pad;
    s32 direction;
    u8  row;
    u8* cursor;
    u8  type;
    u8  next;
    s32 rooms_offset;
    s8  srow;
    s16 x;
    s16 y;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        Fairy_ShowTypeMessage();
        D_801F294D = 0;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        srow = D_801D4E28;
        type = g_FairyListOptionTypes[srow];
        if (type == 0xFF) {
            Fairy_AskConfirm();
        } else {
            rooms_offset = (g_SceneEventState.selection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E2C = g_FairyRooms[rooms_offset + 1];
            } else {
                D_801D4E2C = 0;
            }
            srow       = D_801D4E28;
            D_801D4E1C = g_FairyListOptionTypes[srow];
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_FairyMessage = g_FairyOptionMessages[D_801D4E1C];
            D_801F294D++;
        }
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        row       = D_801D4E28;
        if (direction & PADLup) {
            next       = D_801D4E28 - 1;
            D_801D4E28 = next;
            if ((s8)next < 0) {
                D_801D4E28 = D_801455C3 - 1;
            }
        } else if (direction & PADLdown) {
            next       = D_801D4E28 + 1;
            D_801D4E28 = next;
            if ((s8)next >= D_801455C3) {
                D_801D4E28 = 0;
            }
        }
        if (row != D_801D4E28) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
        srow           = D_801D4E28;
        g_FairyMessage = g_FairyListMessages[srow];
    }
    Fairy_DrawOverview();
    cursor = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*cursor, 1);
    Fairy_GetJobPos(&x, &y, *cursor, 0);
    Fairy_DrawCursor(x, y, 1);
    y = Fairy_GetTypeMenuTop();
    Fairy_DrawTypeMenu((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 0);
    UI_CursorDraw((u16)((52 * ((*cursor - 1) % 4) + 0x44) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E28 * 16), 0);
}

/* Moves the cursor in the option list of the chosen room type and draws the lists. */
/* func_801D1A94 */
MATCH void Fairy_Commu01PickRoomLine(void) {
    u16 pad;
    s32 direction;
    u8* cursor;
    u8  next;
    s32 rooms_offset;
    s8  srow;
    u8  line;
    s16 x;
    s16 y;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801D4E1C = 0xFF;
        D_801F294D--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_FairyOptionLines[D_801D4E1C][1] == 0xFF) {
            Fairy_AskConfirm();
        } else {
            srow         = D_801D4E28;
            rooms_offset = (g_SceneEventState.selection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E30 = g_FairyRooms[rooms_offset + 2];
            } else {
                D_801D4E30 = 0;
            }
            D_801D4E20 = g_FairyOptionLines[D_801D4E1C][1];
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_FairyMessage = 0x46;
            D_801F294D++;
        }
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        line      = D_801D4E2C;
        if (direction & PADLup) {
            next       = D_801D4E2C - 1;
            D_801D4E2C = next;
            if ((s8)next < 0) {
                D_801D4E2C = g_FairyOptionLines[D_801D4E1C][0] - 1;
            }
        } else if (direction & PADLdown) {
            next       = D_801D4E2C + 1;
            D_801D4E2C = next;
            if ((s8)next >= g_FairyOptionLines[D_801D4E1C][0]) {
                D_801D4E2C = 0;
            }
        }
        if (line != D_801D4E2C) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }
    Fairy_DrawOverview();
    cursor = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*cursor, 1);
    Fairy_GetJobPos(&x, &y, *cursor, 0);
    Fairy_DrawCursor(x, y, 1);
    y = Fairy_GetTypeMenuTop();
    Fairy_DrawTypeMenu((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 1);
    if (D_801D4E1C != 0xFF) {
        y = y + (12 + 16 * (s8)D_801D4E28);
        y = Fairy_DrawOptionMenu((s16)(52 * ((*cursor - 1) % 4) + 0x4A), y, D_801D4E1C, 0);
        UI_CursorDraw((u16)((52 * ((*cursor - 1) % 4) + 0x4C) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E2C * 16), 0);
    }
}

/* Toggles the choice of the last option list and draws the lists. */
/* func_801D1E48 */
MATCH void Fairy_Commu01PickRoomPair(void) {
    u16 pad;
    s32 direction;
    u8* row;
    s16 x;
    s16 y;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_FairyMessage = 0x45;
        D_801D4E20     = 0xFF;
        D_801F294D--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        Fairy_AskConfirm();
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        if (direction & (PADLup | PADLdown)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            D_801D4E30 ^= 1;
        }
    }
    Fairy_DrawOverview();
    row = &g_SceneEventState.selection;
    Fairy_DrawCellFrame(*row, 1);
    Fairy_GetJobPos(&x, &y, *row, 0);
    Fairy_DrawCursor(x, y, 1);
    y = Fairy_GetTypeMenuTop();
    Fairy_DrawTypeMenu((s16)(52 * ((*row - 1) % 4) + 0x42), y, 1);
    y = y + (12 + 16 * (s8)D_801D4E28);
    y = Fairy_DrawOptionMenu((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 1);
    if (D_801D4E20 != 0xFF) {
        y = y + (12 + 16 * (s8)D_801D4E2C);
        y = Fairy_DrawOptionMenu((s16)(52 * ((*row - 1) % 4) + 0x52), y, D_801D4E20, 0);
        UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x54) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E30 * 16), 0);
    }
}

/* Answers whether to keep the room settings: yes stores them in the room record, no returns; redraws the lists. */
/* func_801D2110 */
MATCH void Fairy_Commu01ConfirmRoom(void) {
    u16 pad;
    u32 anchor;
    s32 direction;
    s32 index;
    s32 i;
    u8  stale;
    u8* rec;
    u8* sel;
    u8* cursor;
    u8* row;
    s16 x;
    s16 y;

    pad   = g_PadStates[0].pressed;
    stale = 0;
    if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_FairyConfirmChoice != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            g_FairyMessage = g_FairyReturnMessage;
            D_801F294D     = g_FairyReturnStep;
        } else {
            index = g_SceneEventSelection - 1;
            if (g_FairyRooms[index * 8] != (s8)D_801D4E28 + 4 || D_801457A9[index][0] != (s8)D_801D4E2C || D_801457AA[index][0] != (s8)D_801D4E30) {
                stale = 1;
            }
            if (stale) {
                rec = &g_SceneEventSelection;
                for (i = 0; i < FAIRY_JOB_COUNT; i++) {
                    if (g_FairyJobs[i].type == *rec) {
                        anchor                         = COMMU_REQUEST_ANCHOR(rec);
                        g_FairyJobs[i].record_state    = 0;
                        g_FairyJobs[i].unk_03          = 0;
                        g_FairyJobs[i].progress_anchor = anchor;
                    }
                }
                sel                      = &g_SceneEventSelection;
                index                    = *sel - 1;
                D_801457AB[index][0]     = 0;
                index                    = *sel - 1;
                (&D_801457AC)[index * 2] = g_BattleCount;
            }
            cursor                      = &g_SceneEventSelection;
            /* The room-type byte leads the row the grid-line column starts. */
            D_801457A9[*cursor - 1][-1] = D_801D4E28 + 4;
            D_801457A9[*cursor - 1][0]  = D_801D4E2C;
            D_801457AA[*cursor - 1][0]  = D_801D4E30;
            g_FairyCursorColumn         = g_FairySavedCursorColumn;
            g_FairyCursorGridRow        = g_FairySavedCursorGridRow;
            g_FairyCursorZone           = g_FairySavedCursorZone;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            g_FairyMessage = 0xB5;
            D_801F294C     = D_801F294C - 1;
        }
    } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_FairyMessage = g_FairyReturnMessage;
        D_801F294D     = g_FairyReturnStep;
    } else {
        direction = INPUT_REPEATED(pad, (PADLleft | PADLright));
        if (direction & (PADLleft | PADLright)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            g_FairyConfirmChoice ^= 1;
        }
    }
    Fairy_DrawOverview();
    row = &g_SceneEventSelection;
    Fairy_DrawCellFrame(*row, 1);
    Fairy_GetJobPos(&x, &y, *row, 0);
    Fairy_DrawCursor(x, y, 1);
    y = Fairy_GetTypeMenuTop();
    if (D_801D4E1C == 0xFF) {
        Fairy_DrawTypeMenu((s16)(52 * ((*row - 1) % 4) + 0x42), y, 0);
        UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x44) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E28 * 16), 0);
    } else {
        Fairy_DrawTypeMenu((s16)(52 * ((*row - 1) % 4) + 0x42), y, 1);
        y = y + (12 + 16 * (s8)D_801D4E28);
        if (D_801D4E20 == 0xFF) {
            y = Fairy_DrawOptionMenu((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 0);
            UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x4C) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E2C * 16), 0);
        } else {
            y = Fairy_DrawOptionMenu((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 1);
            y = y + (12 + 16 * (s8)D_801D4E2C);
            y = Fairy_DrawOptionMenu((s16)(52 * ((*row - 1) % 4) + 0x52), y, D_801D4E20, 0);
            UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x54) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E30 * 16), 0);
        }
    }
}

#include "overlays/commu/shared/Commu_CellGrid.h"

/* Draws the grid of a fairy box. */
/* func_801D273C */
MATCH void Fairy_DrawChannelGrid(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(Fairy_DrawPiece, 0x22, 7, 4, 6);
}

/* Draws the box of one fairy: its name and four channel bars. */
/* func_801D28A4 */
MATCH void Fairy_DrawChannelBox(s16 x, s16 y, u8 slot, s32 selected) {
    TILE* prim;
    u8*   block;
    u8*   names;
    u32   offset;
    s8    row;
    s32   index;
    u8    sel;
    u8    type;

    /* The window style leads the shared block; the five-byte name rows sit 0xE96 above it. */
    block = &g_WindowStyle;
    func_801AE3F0((u16)(x + 4), (u16)(y + 4), 0x48, 0x28, 0x81, block[0]);
    func_801AE3F0((u16)x, (u16)y, 0x48, 0x26, 0x80, block[0]);
    Fairy_DrawChannelGrid(x, y);
    offset = slot * 5;
    names  = block + 0xE96;
    func_8014F800((s16)(x + 6), (s16)(y + 4), 0, 5, (u32)&names[offset]);
    prim = GFX_CURSOR(TILE);
    SetTile(prim);
    setXY0(prim, x + 6, y + 0x12);
    setWH(prim, 0x3C, 0x10);
    setRGB0(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
    sel = selected;
    if (sel == 0) {
        Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 0);
        Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 0);
        Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 0);
        Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 0);
    } else {
        row = D_801D4E28;
        if (row == 0) {
            type = 0;
        } else if (row > 8) {
            type = row - 8;
        } else {
            index = row - 1;
            type  = g_FairyRooms[index * 8];
        }
        if (g_FairyBlinkChannels[type] == 0) {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 1);
        } else {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 0);
        }
        if (g_FairyBlinkChannels[type] == 1) {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 1);
        } else {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 0);
        }
        if (g_FairyBlinkChannels[type] == 2) {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 1);
        } else {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 0);
        }
        if (g_FairyBlinkChannels[type] == 3) {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 1);
        } else {
            Fairy_DrawChannelBar((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 0);
        }
    }
}

/* The four channel bar colours g_FairyChannelColors holds, one RGB triple per bar. */
typedef struct {
    u8 rgb[4][3];
} FairyBarColors;

/* Draws one channel bar as two shaded quads that meet on the middle row; a blinking bar pulses with the frame count. */
/* func_801D2D98 */
MATCH void Fairy_DrawChannelBar(s16 x, s16 y, s16 width, u8 channel, u8 blink) {
    FairyBarColors colors;
    u8*            rgb;
    s32            scale;
    POLY_G4*       poly;
    s16            middle;

    colors = *(FairyBarColors*)g_FairyChannelColors;
    if (blink) {
        if (g_FrameCount & 8) {
            scale = (g_FrameCount & 6) << 5 | 0x3F;
        } else {
            scale = (~g_FrameCount & 6) << 5 | 0x3F;
        }
    } else {
        scale = 0x80;
    }

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    poly->x0 = x;
    poly->x1 = x + width;
    poly->y2 = y + 2;
    poly->y0 = y;
    poly->y1 = y;
    poly->x2 = poly->x0;
    middle   = y + 2;
    poly->y3 = middle;
    poly->x3 = poly->x1;
    rgb      = colors.rgb[channel];
    setRGB2(poly, rgb[0] * scale, rgb[1] * scale, rgb[2] * scale);
    setRGB0(poly, poly->r2 >> 2, poly->g2 >> 2, poly->b2 >> 2);
    setRGB3(poly, poly->r2, poly->g2, poly->b2);
    setRGB1(poly, poly->r0, poly->g0, poly->b0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    poly->x0 = x;
    poly->y0 = middle;
    poly->x1 = x + width;
    poly->y1 = middle;
    poly->x2 = poly->x0;
    poly->y2 = y + 4;
    poly->x3 = poly->x1;
    poly->y3 = y + 4;
    setRGB0(poly, rgb[0] * scale, rgb[1] * scale, rgb[2] * scale);
    setRGB2(poly, poly->r0 >> 2, poly->g0 >> 2, poly->b0 >> 2);
    setRGB1(poly, poly->r0, poly->g0, poly->b0);
    setRGB3(poly, poly->r2, poly->g2, poly->b2);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
}

#define FAIRY_OVERVIEW_JOB_TYPE_COUNT  3
#define FAIRY_OVERVIEW_ROOM_COUNT      8
#define FAIRY_OVERVIEW_ROOM_COLUMNS    4
#define FAIRY_OVERVIEW_JOB_COLUMNS     5
#define FAIRY_OVERVIEW_COLUMN_STEP     0x34
#define FAIRY_OVERVIEW_ROW_STEP        0x3D
#define FAIRY_OVERVIEW_JOB_ROW_STEP    0x36
#define FAIRY_OVERVIEW_JOB_COLUMN_STEP 8
#define FAIRY_OVERVIEW_ROOM_X(room)    (((room) % FAIRY_OVERVIEW_ROOM_COLUMNS) * FAIRY_OVERVIEW_COLUMN_STEP)
#define FAIRY_OVERVIEW_ROOM_Y(room)    (((room) / FAIRY_OVERVIEW_ROOM_COLUMNS) * FAIRY_OVERVIEW_ROW_STEP)

/* Draws the fairy job overview and the unlocked room cells. */
/* func_801D3038 */
MATCH void Fairy_DrawOverview(void) {
    TILE* tile;
    u8*   buffer;
    s16   marker_x;
    s16   marker_y;
    s32   shade;
    s32   y;
    u8    entry_row;
    u8    row;
    u8    column;
    u8    room_type;
    u8    count;
    u8    active;
    u8    i;
    u8    job;

    UI_WindowDraw(0x14, 0x12, 0x118, 0x13, 0xF2, g_WindowStyle);
    UI_WindowDrawOutline(0x16, 0x14, 0x113, 0x0F, 0);
    if (g_FairyMessage != 0xFFFF) {
        UI_TextDraw(0x1D, 0x15, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, g_FairyMessage));

        if (g_FairyMessage == 0x3D) {
            GFX_ADD_DRAW_MODE(getTPage(0, 0, 0, 0));
            shade = ((g_FrameCount & 8) ? (g_FrameCount & 6) : (~g_FrameCount & 6)) << 5 | 0x3F;
            tile  = GFX_CURSOR(TILE);
            SetTile(tile);
            SetSemiTrans(tile, 1);
            entry_row = g_FairyConfirmChoice;
            tile->y0  = 0x16;
            tile->h   = 0x0C;
            setRGB0(tile, shade, shade, 0);
            tile->x0 = (entry_row << 5) + 0xF4;
            tile->w  = 0x19 - entry_row * 8;
            GFX_AddPrim(1, sizeof(TILE));
        }
    }

    UI_WindowDraw(0x15, 0x2E, 0x114, 0xAA, 0x80, g_WindowStyle);
    Fairy_DrawOverviewGrid(0x14, 0x2D);
    UI_WindowDrawOutline(0x20, 0x38, 0xA8, 0x10, 1);

    count = Fairy_GetJobActive(FAIRY_JOB_IDLE);
    for (i = 0; i < count; i++) {
        Fairy_DrawPiece(0x24 + i * FAIRY_OVERVIEW_JOB_COLUMN_STEP, 0x3A, 1);
    }

    for (i = 0; i < FAIRY_OVERVIEW_JOB_TYPE_COUNT; i++) {
        y = i * FAIRY_OVERVIEW_JOB_ROW_STEP;
        UI_WindowDrawOutline(0xF2, (s16)(y + 0x36), 0x30, 0x30, 1);
        Fairy_DrawPiece(0xEF, y + 0x33, i + 3);
        active = Fairy_GetJobActive(FAIRY_JOB_HUNT + i);
        for (job = 0; job < active; job++) {
            column = job % FAIRY_OVERVIEW_JOB_COLUMNS;
            row    = job / FAIRY_OVERVIEW_JOB_COLUMNS;
            Fairy_DrawPiece(0xF6 + column * FAIRY_OVERVIEW_JOB_COLUMN_STEP, y + 0x44 + row * 7, 1);
        }
    }

    for (i = 0; i < FAIRY_OVERVIEW_ROOM_COUNT; i++) {
        UI_WindowDrawOutline((s16)(FAIRY_OVERVIEW_ROOM_X(i) + 0x20), (s16)(FAIRY_OVERVIEW_ROOM_Y(i) + 0x6B), 0x28, 0x28, 1);
        if (i >= D_801F286D[g_GameAreaId]) {
            UI_WindowDraw(FAIRY_OVERVIEW_ROOM_X(i) + 0x20, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6B, 0x28, 0x28, 1, g_WindowStyle);
        } else {
            Fairy_DrawPiece(FAIRY_OVERVIEW_ROOM_X(i) + 0x1A, FAIRY_OVERVIEW_ROOM_Y(i) + 0x5B, 0);
            room_type = g_FairyRooms[i * 8];
            if (room_type != 0) {
                if (room_type != 5) {
                    Fairy_DrawRoomIcon(FAIRY_OVERVIEW_ROOM_X(i) + 0x22, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6C, g_FairyRoomIcons[room_type]);
                } else {
                    Fairy_DrawRoomIcon(FAIRY_OVERVIEW_ROOM_X(i) + 0x22, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6C, g_FairyRoomIcons[5] + D_801457A9[i][0]);
                }
            }
            active = Fairy_GetJobActive(i + 1);
            for (job = 1; job <= active; job++) {
                Fairy_GetJobPos(&marker_x, &marker_y, (u8)(i + 1), job);
                Fairy_DrawPiece(marker_x, marker_y, 1);
            }
        }
    }

    Fairy_DrawPiece(0x30, 0x4C, 2);
    buffer = g_UiTextFormatBuffer;
    sprintf((char*)buffer, D_801D0C10, D_801455C2);
    UI_TextDrawAscii(0x50, 0x4C, 0, buffer);
    UI_TextDraw(0x78, 0x4C, 0, 7, D_801D4C30);
    sprintf((char*)buffer, D_801D0C14, D_801455C4);
    UI_TextDrawAscii(0xB8, 0x4C, 0, buffer);
}

/* Draws the grid over the body of the overview window. */
/* func_801D3594 */
MATCH void Fairy_DrawOverviewGrid(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(Fairy_DrawPiece, 0xA8, 33, 20, 8);
}

/* Outlines the cell with its top and right edges, then its left and bottom, yellow when selected and blinking with the frame count otherwise. */
/* func_801D36FC */
MATCH void Fairy_DrawCellFrame(s32 cell, s32 selected) {
    LINE_F3* prim;
    s32      shade;
    s32      state;
    u8       cell_index;

    cell_index = cell;
    if ((selected & BYTE_MASK) == 0) {
        state = g_FrameCount;
        if (state & 0x8) {
            shade = (state & 0x6) << 5 | 0x3F;
        } else {
            shade = (~state & 0x6) << 5 | 0x3F;
        }
    } else {
        shade = 0xFF;
    }

    prim = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(prim);
    if (cell_index != 0 && cell_index < COMMU_CELL_FRAME_COUNT && D_801F286D[g_GameAreaId] < cell_index) {
        prim->x0 = g_FairyCellFrames[cell_index].points[1][0];
    } else {
        prim->x0 = g_FairyCellFrames[cell_index].points[0][0];
    }
    prim->y0 = g_FairyCellFrames[cell_index].points[0][1];
    prim->x1 = g_FairyCellFrames[cell_index].points[2][0];
    prim->y1 = g_FairyCellFrames[cell_index].points[0][1];
    prim->x2 = g_FairyCellFrames[cell_index].points[2][0];
    prim->y2 = g_FairyCellFrames[cell_index].points[2][1];
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F3));

    prim = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(prim);
    if (cell_index != 0 && cell_index < COMMU_CELL_FRAME_COUNT && D_801F286D[g_GameAreaId] < cell_index) {
        prim->y0 = g_FairyCellFrames[cell_index].points[0][1];
    } else {
        prim->y0 = g_FairyCellFrames[cell_index].points[1][1];
    }
    prim->x0 = g_FairyCellFrames[cell_index].points[1][0];
    prim->x1 = g_FairyCellFrames[cell_index].points[1][0];
    prim->y1 = g_FairyCellFrames[cell_index].points[2][1];
    prim->x2 = g_FairyCellFrames[cell_index].points[2][0];
    prim->y2 = g_FairyCellFrames[cell_index].points[2][1];
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F3));
}

/* Draws the blinking triangle cursor at a point. */
/* func_801D3984 */
MATCH void Fairy_DrawCursor(s32 x, s32 y, s32 bright) {
    POLY_F3* poly;
    u8       colour;

    COMMU_DRAW_CURSOR_TRIANGLE(x, y, bright);
}

/* Returns how many active jobs have the job type. */
/* func_801D3A48 */
MATCH u8 Fairy_GetJobActive(u8 job_type) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < FAIRY_JOB_COUNT; i++) {
        if (g_FairyJobs[i].active != 0) {
            if (g_FairyJobs[i].type == job_type) {
                count++;
            }
        }
    }
    return count;
}

/* Returns the slot of the index-th active job of a job type, or GAME_NONE. */
/* func_801D3AA0 */
MATCH u8 Fairy_FindJob(u8 type, u8 index) {
    u8  count;
    s32 i;

    count = 0;
    for (i = 0; i < FAIRY_JOB_COUNT; i++) {
        if (g_FairyJobs[i].active != 0) {
            if (g_FairyJobs[i].type == type) {
                if (count == index) {
                    return (u8)i;
                }
                count++;
            }
        }
    }
    return GAME_NONE;
}

/* Steps the cell cursor over the idle fairies, the room grid and the job types by the pad direction and writes the cell under it. */
/* func_801D3B0C */
MATCH void Fairy_MoveCursor(u8* cell) {
    s32 direction;

    direction = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown | PADLleft | PADLright));
    if (direction & PADLup) {
        switch (g_FairyCursorZone) {
            case FAIRY_CURSOR_IDLE:
                g_FairyCursorGridRow = 1;
                g_FairyCursorZone    = FAIRY_CURSOR_ROOMS;
                *cell                = g_FairyCursorColumn + 4;
                break;
            case FAIRY_CURSOR_ROOMS:
                if (g_FairyCursorGridRow == 0) {
                    g_FairyCursorZone = FAIRY_CURSOR_IDLE;
                    *cell             = 0;
                } else {
                    g_FairyCursorGridRow = 0;
                    *cell                = *cell - 4;
                }
                break;
            case FAIRY_CURSOR_JOBS:
                *cell = *cell - 1;
                if (*cell < FAIRY_JOB_HUNT) {
                    *cell = FAIRY_JOB_BUILD;
                }
                break;
        }
    } else if (direction & PADLdown) {
        switch (g_FairyCursorZone) {
            case FAIRY_CURSOR_IDLE:
                g_FairyCursorGridRow = 0;
                g_FairyCursorZone    = FAIRY_CURSOR_ROOMS;
                *cell                = g_FairyCursorColumn;
                break;
            case FAIRY_CURSOR_ROOMS:
                if (g_FairyCursorGridRow != 0) {
                    g_FairyCursorZone = FAIRY_CURSOR_IDLE;
                    *cell             = 0;
                } else {
                    g_FairyCursorGridRow = 1;
                    *cell                = *cell + 4;
                }
                break;
            case FAIRY_CURSOR_JOBS:
                *cell = *cell + 1;
                if (*cell > FAIRY_JOB_BUILD) {
                    *cell = FAIRY_JOB_HUNT;
                }
                break;
        }
    } else if (direction & PADLleft) {
        switch (g_FairyCursorZone) {
            case FAIRY_CURSOR_IDLE:
                g_FairyCursorZone = FAIRY_CURSOR_JOBS;
                *cell             = 9;
                break;
            case FAIRY_CURSOR_ROOMS:
                g_FairyCursorColumn = g_FairyCursorColumn - 1;
                *cell               = *cell - 1;
                if (g_FairyCursorColumn == 0) {
                    g_FairyCursorColumn = 1;
                    g_FairyCursorZone   = FAIRY_CURSOR_JOBS;
                    *cell               = g_FairyCursorGridRow + FAIRY_JOB_CLEAR;
                }
                break;
            case FAIRY_CURSOR_JOBS:
                if (*cell == FAIRY_JOB_HUNT) {
                    g_FairyCursorZone = FAIRY_CURSOR_IDLE;
                    *cell             = 0;
                } else {
                    g_FairyCursorZone    = FAIRY_CURSOR_ROOMS;
                    g_FairyCursorGridRow = *cell - FAIRY_JOB_CLEAR;
                    *cell                = (*cell << 2) - 0x24;
                    g_FairyCursorColumn  = 4;
                }
                break;
        }
    } else if (direction & PADLright) {
        switch (g_FairyCursorZone) {
            case FAIRY_CURSOR_IDLE:
                g_FairyCursorZone = FAIRY_CURSOR_JOBS;
                *cell             = 9;
                break;
            case FAIRY_CURSOR_ROOMS:
                g_FairyCursorColumn = g_FairyCursorColumn + 1;
                *cell               = *cell + 1;
                if (g_FairyCursorColumn >= 5) {
                    g_FairyCursorColumn = 4;
                    g_FairyCursorZone   = FAIRY_CURSOR_JOBS;
                    *cell               = g_FairyCursorGridRow + FAIRY_JOB_CLEAR;
                }
                break;
            case FAIRY_CURSOR_JOBS:
                if (*cell == FAIRY_JOB_HUNT) {
                    g_FairyCursorZone = FAIRY_CURSOR_IDLE;
                    *cell             = 0;
                } else {
                    g_FairyCursorZone    = FAIRY_CURSOR_ROOMS;
                    g_FairyCursorColumn  = 1;
                    g_FairyCursorGridRow = *cell - FAIRY_JOB_CLEAR;
                    *cell                = (*cell - FAIRY_JOB_CLEAR) * 4 + 1;
                }
                break;
        }
    }
    if (direction & (PADLup | PADLdown | PADLleft | PADLright)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
}

/* Draws the icon of a room type. */
/* func_801D3EFC */
MATCH void Fairy_DrawRoomIcon(s16 x, s16 y, u8 icon) {
    s32      page;
    SPRT_16* sprite;

    page = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    GFX_SET_DRAW_MODE(page);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    sprite = GFX_CURSOR(SPRT_16);
    SetSprt16(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, (icon % 10) * 16 + 0x50 - (icon / 10) * 0x30, (icon / 10) * 16 - 0x20);
    sprite->clut = (g_FairyIconCluts[icon] >> 4) | 0x7840;
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_16));
}

/* Draws one piece of the piece table at a point: a window frame tile, a fairy or a marker. */
/* func_801D4030 */
MATCH void Fairy_DrawPiece(s16 x, s16 y, u8 piece) {
    s32   page;
    SPRT* sprite;

    page = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    GFX_SET_DRAW_MODE(page);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    setXY0(sprite, x, y);
    setUV0(sprite, g_FairyPieces[piece].u, g_FairyPieces[piece].v);
    setWH(sprite, g_FairyPieces[piece].w, g_FairyPieces[piece].h);
    sprite->clut = getClut(g_FairyPieces[piece].clut_x, g_FairyPieces[piece].clut_y + 0x1E0);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

/* Draws the room type list window with its captions. */
/* func_801D4178 */
MATCH void Fairy_DrawTypeMenu(s16 x, s16 y, u8 mode) {
    s32 i;
    u16 height;
    s32 span;
    u8* count;

    count  = &D_801455C3;
    height = *count << 4;
    span   = height;
    if (mode == 0) {
        UI_WindowDraw((u16)(x + 4), (u16)(y + 5), 0x30, span, UI_WINDOW_OPEN_TOP_LEFT | UI_WINDOW_STYLE_DARK, g_WindowStyle);
    }
    UI_WindowDraw((u16)x, (u16)y, 0x50, height | 1, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);
    Fairy_DrawMenuFrame((s16)x, (s16)(y - 1), span & 0xF0);
    i = 0;
    if (i < *count) {
        do {
            UI_TextDraw((s16)(x + 8), (s16)(y + 2 + i * 16), (mode * 7) & BYTE_MASK, 8, g_FairyMenuText[i]);
            i++;
        } while (i < D_801455C3);
    }
}

/* Draws the frame around a list window of the given height. */
/* func_801D42DC */
MATCH void Fairy_DrawMenuFrame(s16 x, s16 y, u8 height) {
    /* FAKE: retail frame reserves 8 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 8);
    s32 i;
    s32 offset;
    u8  count;

    Fairy_DrawPiece(x, y, 6);
    for (i = 0; i < 8; i++) {
        offset = i * 8 + 8;
        Fairy_DrawPiece((s16)(x + offset), y, 7);
        Fairy_DrawPiece((s16)(x + offset), (s16)(y + height), 0xC);
    }
    Fairy_DrawPiece((s16)(x + 0x48), y, 8);
    count = (height >> 3) - 1;
    i     = 0;
    if (count != 0) {
        do {
            offset = i * 8 + 8;
            Fairy_DrawPiece(x, (s16)(y + offset), 9);
            Fairy_DrawPiece((s16)(x + 0x48), (s16)(y + offset), 0xA);
            i++;
        } while (i < count);
    }
    Fairy_DrawPiece(x, (s16)(y + height), 0xB);
    Fairy_DrawPiece((s16)(x + 0x48), (s16)(y + height), 0xD);
}

/* Returns the top of the room type list window. */
/* func_801D4474 */
MATCH s32 Fairy_GetTypeMenuTop(void) {
    s32 val;
    u32 v;

    if (g_FairyCursorGridRow == 0) {
        v   = D_801455C3;
        val = 0x6A;
        if (v >= 5) {
            v -= 4;
            val = 0x6A - (v * 9);
        }
    } else {
        val = 0xAC - D_801455C3 * 12;
    }
    return (s16)val;
}

/* Draws the option list of a room type and returns its top. */
/* func_801D44E0 */
MATCH s16 Fairy_DrawOptionMenu(s16 x, s16 y, u8 type, u8 mode) {
    s32 i;
    s32 height;
    s32 bottom;
    u16 span;
    u8  rows;

    rows   = g_FairyOptionRows[type].count;
    height = rows << 4;
    span   = height;
    bottom = span + 4;
    if (y + bottom >= 0xD9) {
        y = 0xD4 - height;
    }
    if (mode == 0) {
        UI_WindowDraw((u16)(x + 4), (u16)(y + 6), 0x30, span, UI_WINDOW_OPEN_TOP_LEFT | UI_WINDOW_STYLE_DARK, g_WindowStyle);
    }
    UI_WindowDraw((u16)x, (u16)y, 0x50, height | 1, UI_WINDOW_OPEN_TOP_LEFT, g_WindowStyle);
    Fairy_DrawMenuFrame((s16)x, (s16)(y - 1), span & 0xF0);
    i = 0;
    if (i < g_FairyOptionRows[type].count) {
        do {
            UI_TextDraw((s16)(x + 8), (s16)(y + 2 + i * 16), (mode * 7) & BYTE_MASK, 8, g_FairyMenuText[g_FairyOptionRows[type].first + i + FAIRY_TYPE_LIST_ROWS]);
            i++;
        } while (i < g_FairyOptionRows[type].count);
    }
    return y;
}

/* Writes the screen position of the ordinal-th job of a job type (0 is the cell itself) through the two pointers. */
/* func_801D4694 */
MATCH void Fairy_GetJobPos(s16* out_x, s16* out_y, s32 type, s32 ordinal) {
    s32 base;
    s32 row;
    s32 slot;
    s32 x;
    s32 y;
    s32 sum_x;
    s32 sum_y;
    u8  slots;

    slot = 0;
    type &= BYTE_MASK;
    base  = type - 1;
    x     = base % 4 * 52 + 0x20;
    row   = base >> 2;
    y     = row * 61 + 0x6B;
    slots = Fairy_GetJobActive(type);
    switch (slots) {
        case 2:
            slot = 2;
            break;
        case 3:
            slot = 1;
            break;
    }
    if (ordinal & BYTE_MASK) {
        ordinal--;
        sum_x  = x + g_FairyJobSlots[slot + (ordinal & BYTE_MASK)].x;
        *out_x = sum_x;
        sum_y  = y + g_FairyJobSlots[slot + (ordinal & BYTE_MASK)].y;
        *out_y = sum_y;
    } else {
        *out_x = x + 0xA;
        *out_y = y;
    }
}

/* Puts back the cursor the move started from and steps back one sub-step. */
/* func_801D47C4 */
MATCH void Fairy_RestoreCursor(void) {
    g_FairyCursorColumn  = g_FairySavedCursorColumn;
    g_FairyCursorGridRow = g_FairySavedCursorGridRow;
    g_FairyCursorZone    = g_FairySavedCursorZone;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    D_801F294D--;
}

/* Moves the job at the cursor to the picked job type and returns whether it went through. */
/* func_801D482C */
MATCH s32 Fairy_MoveJob(s32 ordinal_offset) {
    s32 committed;
    u8  slot;
    u8  step;
    u32 anchor;

    committed = 0;
    switch (g_FairyCursorZone) {
        case FAIRY_CURSOR_ROOMS:
            if (Fairy_GetJobActive(D_801D4E28) == 3) {
                break;
            }
            if (D_801F286D[g_GameAreaId] < (s8)D_801D4E28) {
                break;
            }
        case FAIRY_CURSOR_IDLE:
        case FAIRY_CURSOR_JOBS:
            if ((s8)D_801D4E28 == g_SceneEventState.selection) {
                break;
            }
            g_FairyCursorColumn               = g_FairySavedCursorColumn;
            g_FairyCursorGridRow              = g_FairySavedCursorGridRow;
            g_FairyCursorZone                 = g_FairySavedCursorZone;
            slot                              = Fairy_FindJob(g_SceneEventState.selection, g_FairyJobOrdinal - ordinal_offset);
            g_FairyJobs[slot].type            = D_801D4E28;
            anchor                            = g_BattleCount;
            g_FairyJobs[slot].record_state    = 0;
            g_FairyJobs[slot].unk_03          = 0;
            step                              = D_801F294C - 1;
            g_FairyJobs[slot].progress_anchor = anchor;
            D_801F294C                        = step;
            committed                         = 1;
            break;
    }
    SND_SEPlay((committed & BYTE_MASK) ? EMI_SE_ID(SND_BANK_COMMON, 3) : EMI_SE_ID(SND_BANK_COMMON, 7));
    return committed;
}

/* Sets the top message from the selected cell. */
/* func_801D49C4 */
MATCH void Fairy_ShowTypeMessage(void) {
    u16 text_ids[9];
    u32 row;
    u8  room_type;
    s32 room_offset;
    u8  type_index;
    u16 text_id;
    u16 room_text_id;

    memcpy(text_ids, D_801D0C18, sizeof(text_ids));
    row = g_SceneEventState.selection;
    if ((row & BYTE_MASK) == 0) {
        text_id = 0x6A;
    } else if ((row & BYTE_MASK) >= FAIRY_JOB_HUNT) {
        text_id = row * 2 + 0x2C;
    } else {
        room_offset = ((row & BYTE_MASK) - 1) * 8;
        room_type   = g_FairyRooms[room_offset];
        if (room_type == 0) {
            room_text_id = 0x6A;
        } else {
            type_index = (room_type - 4) & BYTE_MASK;
            if (type_index == 0) {
                room_text_id = g_FairyRooms[room_offset + 1] + 0x4A;
            } else {
                room_text_id = text_ids[type_index - 1];
            }
        }
        text_id = room_text_id;
    }
    g_FairyMessage = text_id;
}

/* Sets the top message from the cell the target cursor is on. */
/* func_801D4AAC */
MATCH void Fairy_ShowTargetMessage(u8* target) {
    u32 row;
    u32 limit;
    u8  room_type;
    s32 room_offset;
    u16 text_id;
    u16 row_text_id;

    row = *target;
    if (row == g_SceneEventState.selection) {
        text_id = 0x44;
    } else if (row == 0) {
        text_id = 0x69;
    } else if (row >= FAIRY_JOB_HUNT) {
        text_id = g_FairyJobMessages[row];
    } else {
        limit = D_801F286D[g_GameAreaId];
        if (limit < row) {
            row_text_id = 0x44;
        } else {
            room_offset = (row - 1) * 8;
            room_type   = g_FairyRooms[room_offset];
            if (room_type == 0) {
                row_text_id = 0x69;
            } else {
                row_text_id = g_FairyRoomMessages[room_type];
            }
        }
        text_id = row_text_id;
    }
    g_FairyMessage = text_id;
}

/* Shows the confirm question, keeping the sub-step and message to return to. */
/* func_801D4B58 */
MATCH void Fairy_AskConfirm(void) {
    g_FairyReturnStep    = D_801F294D;
    g_FairyReturnMessage = g_FairyMessage;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
    g_FairyMessage       = 61;
    g_FairyConfirmChoice = 0;
    D_801F294D           = 5;
}
