#include "commu01_07.h"
#include "overlays/commu/shared/Commu_CursorTriangle.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu01 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C2C(void) {
    SYS_DISPATCH_BYTE(g_Commu01Steps, D_801F294C);
}

MATCH void func_801D0C68(void) {
    D_801D4DF4 = 1;
    D_801D4DF8 = 0;
    D_801D4DFC = 0;
    D_801D4E0C = 181;
    D_801F294C++;
}

/* Confirms the commu entry request of the selected row, or moves the row. */
MATCH void func_801D0CAC(void) {
    u16 pad;
    u8* counter;
    u8  mode;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        counter    = (u8*)&g_SceneEventState.step;
        D_801D4E0C = 0xFFFF;
        *counter += 1;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        D_801F294D = 0;
        D_801D4E24 = 0;
        D_801D4E00 = D_801D4DF4;
        D_801D4E04 = D_801D4DF8;
        mode       = D_801D4DFC;
        D_801D4E08 = mode;
        switch (mode) {
            case 0:
            case 2:
                if (Fairy_GetJobActive(g_SceneEventState.selection) != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                    func_801D49C4();
                    D_801F294C++;
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case 1:
                if (D_801F286D[g_GameAreaId] < g_SceneEventState.selection) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
                    func_801D49C4();
                    D_801F294C++;
                }
                break;
            default:
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                break;
        }
    } else {
        func_801D3B0C(&g_SceneEventState.selection);
    }
    func_801D3038();
    func_801D36FC(g_SceneEventState.selection, 0);
}

MATCH void func_801D0E44(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Steps, D_801D4E08);
}

MATCH void func_801D0E80(void) {
    SYS_DISPATCH_BYTE(D_801D4BE4, D_801F294D);
}

/* Moves the ordinal of the selected record type and draws its cell. */
MATCH void func_801D0EBC(void) {
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
        D_801D4E0C = 0xB5;
        D_801F294C--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        D_801D4E0C = 0x44;
        D_801D4E28 = g_SceneEventState.selection;
        D_801F294D++;
    } else {
        count     = Fairy_GetJobActive(g_SceneEventState.selection);
        direction = INPUT_REPEATED(*pad_word, (PADLleft | PADLright));
        ordinal   = D_801D4E24;
        if (direction & PADLright) {
            D_801D4E24 = ordinal + 1;
            if ((s8)(ordinal + 1) == count) {
                D_801D4E24 = 0;
            }
        } else if (direction & PADLleft) {
            D_801D4E24 = ordinal - 1;
            if ((s8)(ordinal - 1) < 0) {
                D_801D4E24 = count - 1;
            }
        }
        if (ordinal != D_801D4E24) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }
    func_801D3038();
    row = &g_SceneEventState.selection;
    func_801D36FC(*row, 1);
    if (*row == 0) {
        ordinal = D_801D4E24;
        /* Eight pixels a row, sign extended before the scale. */
        offset  = ((s32)ordinal << 24) >> 21;
        func_801D3984(offset + 0x28, 0x39, 0);
        func_801D28A4(offset + 0x30, 0x42, func_801D3AA0(*row, D_801D4E24), 0);
    } else {
        col  = (s8)D_801D4E24 % 5;
        line = (s8)D_801D4E24 / 5;
        x    = col * 8;
        y    = (*row - 9) * 54 + line * 7;
        func_801D3984(x + 0xFA, (s16)(y + 0x44), 0);
        func_801D28A4(x + 0xA8, (s16)(y + 0x4C), func_801D3AA0(*row, D_801D4E24), 0);
    }
}

/* Commits the request row or moves it, then draws the row and its cell. */
MATCH void func_801D1158(void) {
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
        func_801D49C4();
        func_801D47C4();
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        committed = func_801D482C(0);
        if (committed & BYTE_MASK) {
            D_801D4E0C = 0xB5;
        }
    } else {
        row = &D_801D4E28;
        func_801D3B0C(row);
        func_801D4AAC(row);
    }
    func_801D3038();
    row = &g_SceneEventState.selection;
    func_801D36FC(*row, 1);
    func_801D36FC(D_801D4E28, 0);
    if ((committed & BYTE_MASK) == 0) {
        if (*row == 0) {
            func_801D3984((s8)D_801D4E24 * 8 + 0x28, 0x39, 1);
        } else {
            /* The inset stays a value of its own: folded, it lands one slot early. */
            line_inset = 0x44;
            col        = (s8)D_801D4E24 % 5;
            line       = (s8)D_801D4E24 / 5;
            y          = (*row - 9) * 54 + (line * 7 + line_inset);
            func_801D3984(col * 8 + 0xFA, (s16)y, 1);
        }
        func_801D28A4(0xA0, 0x3E, func_801D3AA0(g_SceneEventState.selection, D_801D4E24), 1);
    }
}

MATCH void func_801D1328(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Sub1Steps, D_801F294D);
}

/* Reads the fairy room list input and draws the selected room. */
MATCH void func_801D1364(void) {
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
        D_801D4E0C = 181;
        D_801F294C--;
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        row = D_801D4E24;
        if (row != 0) {
            D_801D4E0C = 68;
            D_801D4E28 = g_SceneEventState.selection;
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
        old_row = D_801D4E24;
        count   = Fairy_GetJobActive(g_SceneEventState.selection);
        if (buttons & PADLleft) {
            D_801D4E24--;
            if ((s8)D_801D4E24 < 0) {
                D_801D4E24 = count;
            }
        } else if (buttons & PADLright) {
            D_801D4E24++;
            if ((count & BYTE_MASK) < (s8)D_801D4E24) {
                D_801D4E24 = 0;
            }
        }
        if (old_row != D_801D4E24) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }

    func_801D3038();
    selection = &g_SceneEventState.selection;
    func_801D36FC(*selection, 1);
    func_801D4694(&x, &y, *selection, D_801D4E24);
    row = D_801D4E24;
    if (row == 0) {
        func_801D3984((s16)x, y, 0);
    } else {
        func_801D3984((s16)(x + 4), y, 0);
        func_801D28A4((s16)(x + 0x10), (s16)(y - 8), func_801D3AA0(*selection, (D_801D4E24 - 1) & BYTE_MASK) & BYTE_MASK, 0);
    }
}

MATCH void func_801D1630(void) {
    u16 x;
    s16 y;
    s32 result;
    u8* selection;

    result = 0;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        func_801D47C4();
        func_801D49C4();
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        result = func_801D482C(1);
        if (result & BYTE_MASK) {
            D_801D4E0C = 181;
        }
    } else {
        func_801D3B0C(&D_801D4E28);
        func_801D4AAC(&D_801D4E28);
    }
    func_801D3038();
    selection = &g_SceneEventState.selection;
    func_801D36FC(*selection, 1);
    func_801D36FC(D_801D4E28, 0);
    if (!(result & BYTE_MASK)) {
        func_801D4694(&x, &y, *selection, D_801D4E24);
        func_801D3984((s16)(x + 4), y, 1);
        func_801D28A4(0xA0, 0x3E, func_801D3AA0(*selection, (D_801D4E24 - 1) & BYTE_MASK) & BYTE_MASK, 1);
    }
}

/* Moves the request row between types and draws the chosen type. */
MATCH void func_801D1778(void) {
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
        func_801D49C4();
        D_801F294D = 0;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        srow = D_801D4E28;
        type = D_801D4C04[srow];
        if (type == 0xFF) {
            func_801D4B58();
        } else {
            rooms_offset = (g_SceneEventState.selection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E2C = g_FairyRooms[rooms_offset + 1];
            } else {
                D_801D4E2C = 0;
            }
            srow       = D_801D4E28;
            D_801D4E1C = D_801D4C04[srow];
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_801D4E0C = D_801D4C10[D_801D4E1C];
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
        srow       = D_801D4E28;
        D_801D4E0C = D_801D4BB8[srow];
    }
    func_801D3038();
    cursor = &g_SceneEventState.selection;
    func_801D36FC(*cursor, 1);
    func_801D4694(&x, &y, *cursor, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    func_801D4178((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 0);
    UI_CursorDraw((u16)((52 * ((*cursor - 1) % 4) + 0x44) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E28 * 16), 0);
}

/* Moves the request line inside the chosen type and draws its grid. */
MATCH void func_801D1A94(void) {
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
        if (D_801D4C18[D_801D4E1C][1] == 0xFF) {
            func_801D4B58();
        } else {
            srow         = D_801D4E28;
            rooms_offset = (g_SceneEventState.selection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E30 = g_FairyRooms[rooms_offset + 2];
            } else {
                D_801D4E30 = 0;
            }
            D_801D4E20 = D_801D4C18[D_801D4E1C][1];
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_801D4E0C = 0x46;
            D_801F294D++;
        }
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        line      = D_801D4E2C;
        if (direction & PADLup) {
            next       = D_801D4E2C - 1;
            D_801D4E2C = next;
            if ((s8)next < 0) {
                D_801D4E2C = D_801D4C18[D_801D4E1C][0] - 1;
            }
        } else if (direction & PADLdown) {
            next       = D_801D4E2C + 1;
            D_801D4E2C = next;
            if ((s8)next >= D_801D4C18[D_801D4E1C][0]) {
                D_801D4E2C = 0;
            }
        }
        if (line != D_801D4E2C) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        }
    }
    func_801D3038();
    cursor = &g_SceneEventState.selection;
    func_801D36FC(*cursor, 1);
    func_801D4694(&x, &y, *cursor, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    func_801D4178((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 1);
    if (D_801D4E1C != 0xFF) {
        y = y + (12 + 16 * (s8)D_801D4E28);
        y = func_801D44E0((s16)(52 * ((*cursor - 1) % 4) + 0x4A), y, D_801D4E1C, 0);
        UI_CursorDraw((u16)((52 * ((*cursor - 1) % 4) + 0x4C) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E2C * 16), 0);
    }
}

/* Toggles the request pair and draws both type grids. */
MATCH void func_801D1E48(void) {
    u16 pad;
    s32 direction;
    u8* row;
    s16 x;
    s16 y;

    pad = g_PadStates[0].pressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = 0x45;
        D_801D4E20 = 0xFF;
        D_801F294D--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        func_801D4B58();
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        if (direction & (PADLup | PADLdown)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            D_801D4E30 ^= 1;
        }
    }
    func_801D3038();
    row = &g_SceneEventState.selection;
    func_801D36FC(*row, 1);
    func_801D4694(&x, &y, *row, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    func_801D4178((s16)(52 * ((*row - 1) % 4) + 0x42), y, 1);
    y = y + (12 + 16 * (s8)D_801D4E28);
    y = func_801D44E0((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 1);
    if (D_801D4E20 != 0xFF) {
        y = y + (12 + 16 * (s8)D_801D4E2C);
        y = func_801D44E0((s16)(52 * ((*row - 1) % 4) + 0x52), y, D_801D4E20, 0);
        UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x54) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E30 * 16), 0);
    }
}

/* Commits the request pair the pad input selects, then redraws both type grids. */
MATCH void func_801D2110(void) {
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
        if (D_801D4E18 != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            D_801D4E0C = D_801D4E14;
            D_801F294D = D_801D4E10;
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
            D_801D4DF4                  = D_801D4E00;
            D_801D4DF8                  = D_801D4E04;
            D_801D4DFC                  = D_801D4E08;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            D_801D4E0C = 0xB5;
            D_801F294C = D_801F294C - 1;
        }
    } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = D_801D4E14;
        D_801F294D = D_801D4E10;
    } else {
        direction = INPUT_REPEATED(pad, (PADLleft | PADLright));
        if (direction & (PADLleft | PADLright)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            D_801D4E18 ^= 1;
        }
    }
    func_801D3038();
    row = &g_SceneEventSelection;
    func_801D36FC(*row, 1);
    func_801D4694(&x, &y, *row, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    if (D_801D4E1C == 0xFF) {
        func_801D4178((s16)(52 * ((*row - 1) % 4) + 0x42), y, 0);
        UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x44) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E28 * 16), 0);
    } else {
        func_801D4178((s16)(52 * ((*row - 1) % 4) + 0x42), y, 1);
        y = y + (12 + 16 * (s8)D_801D4E28);
        if (D_801D4E20 == 0xFF) {
            y = func_801D44E0((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 0);
            UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x4C) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E2C * 16), 0);
        } else {
            y = func_801D44E0((s16)(52 * ((*row - 1) % 4) + 0x4A), y, D_801D4E1C, 1);
            y = y + (12 + 16 * (s8)D_801D4E2C);
            y = func_801D44E0((s16)(52 * ((*row - 1) % 4) + 0x52), y, D_801D4E20, 0);
            UI_CursorDraw((u16)((52 * ((*row - 1) % 4) + 0x54) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E30 * 16), 0);
        }
    }
}

#include "overlays/commu/shared/Commu_CellGrid.h"

MATCH void func_801D273C(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D4030, 0x22, 7, 4, 6);
}

/* Draws the channel box of one commu record slot. */
MATCH void func_801D28A4(s16 x, s16 y, u8 slot, s32 selected) {
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
    func_801D273C(x, y);
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
        func_801D2D98((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 0);
        func_801D2D98((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 0);
        func_801D2D98((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 0);
        func_801D2D98((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 0);
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
        if (D_801D4C20[type] == 0) {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 1);
        } else {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x12), g_Fairies[slot][5] * 12, 0, 0);
        }
        if (D_801D4C20[type] == 1) {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 1);
        } else {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x16), g_Fairies[slot][6] * 12, 1, 0);
        }
        if (D_801D4C20[type] == 2) {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 1);
        } else {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x1A), g_Fairies[slot][7] * 12, 2, 0);
        }
        if (D_801D4C20[type] == 3) {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 1);
        } else {
            func_801D2D98((s16)(x + 6), (s16)(y + 0x1E), g_Fairies[slot][8] * 12, 3, 0);
        }
    }
}

/* The four stat bar colours D_801D0C04 holds, one RGB triple per bar. */
typedef struct {
    u8 rgb[4][3];
} FairyBarColors;

/* Draws one stat bar as two shaded quads that meet on the middle row; a blinking bar pulses with the frame count. */
MATCH void func_801D2D98(s16 x, s16 y, s16 width, u8 channel, u8 blink) {
    FairyBarColors colors;
    u8*            rgb;
    s32            scale;
    POLY_G4*       poly;
    s16            middle;

    colors = *(FairyBarColors*)D_801D0C04;
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

#define FAIRY_OVERVIEW_GROUP_COUNT     3
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
MATCH void func_801D3038(void) {
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
    if (D_801D4E0C != 0xFFFF) {
        UI_TextDraw(0x1D, 0x15, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, D_801D4E0C));

        if (D_801D4E0C == 0x3D) {
            GFX_ADD_DRAW_MODE(getTPage(0, 0, 0, 0));
            shade = ((g_FrameCount & 8) ? (g_FrameCount & 6) : (~g_FrameCount & 6)) << 5 | 0x3F;
            tile  = GFX_CURSOR(TILE);
            SetTile(tile);
            SetSemiTrans(tile, 1);
            entry_row = D_801D4E18;
            tile->y0  = 0x16;
            tile->h   = 0x0C;
            setRGB0(tile, shade, shade, 0);
            tile->x0 = (entry_row << 5) + 0xF4;
            tile->w  = 0x19 - entry_row * 8;
            GFX_AddPrim(1, sizeof(TILE));
        }
    }

    UI_WindowDraw(0x15, 0x2E, 0x114, 0xAA, 0x80, g_WindowStyle);
    func_801D3594(0x14, 0x2D);
    UI_WindowDrawOutline(0x20, 0x38, 0xA8, 0x10, 1);

    count = Fairy_GetJobActive(0);
    for (i = 0; i < count; i++) {
        func_801D4030(0x24 + i * FAIRY_OVERVIEW_JOB_COLUMN_STEP, 0x3A, 1);
    }

    for (i = 0; i < FAIRY_OVERVIEW_GROUP_COUNT; i++) {
        y = i * FAIRY_OVERVIEW_JOB_ROW_STEP;
        UI_WindowDrawOutline(0xF2, (s16)(y + 0x36), 0x30, 0x30, 1);
        func_801D4030(0xEF, y + 0x33, i + 3);
        active = Fairy_GetJobActive(i + 9);
        for (job = 0; job < active; job++) {
            column = job % FAIRY_OVERVIEW_JOB_COLUMNS;
            row    = job / FAIRY_OVERVIEW_JOB_COLUMNS;
            func_801D4030(0xF6 + column * FAIRY_OVERVIEW_JOB_COLUMN_STEP, y + 0x44 + row * 7, 1);
        }
    }

    for (i = 0; i < FAIRY_OVERVIEW_ROOM_COUNT; i++) {
        UI_WindowDrawOutline((s16)(FAIRY_OVERVIEW_ROOM_X(i) + 0x20), (s16)(FAIRY_OVERVIEW_ROOM_Y(i) + 0x6B), 0x28, 0x28, 1);
        if (i >= D_801F286D[g_GameAreaId]) {
            UI_WindowDraw(FAIRY_OVERVIEW_ROOM_X(i) + 0x20, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6B, 0x28, 0x28, 1, g_WindowStyle);
        } else {
            func_801D4030(FAIRY_OVERVIEW_ROOM_X(i) + 0x1A, FAIRY_OVERVIEW_ROOM_Y(i) + 0x5B, 0);
            room_type = g_FairyRooms[i * 8];
            if (room_type != 0) {
                if (room_type != 5) {
                    func_801D3EFC(FAIRY_OVERVIEW_ROOM_X(i) + 0x22, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6C, D_801D4C34[room_type]);
                } else {
                    func_801D3EFC(FAIRY_OVERVIEW_ROOM_X(i) + 0x22, FAIRY_OVERVIEW_ROOM_Y(i) + 0x6C, D_801D4C34[5] + D_801457A9[i][0]);
                }
            }
            active = Fairy_GetJobActive(i + 1);
            for (job = 1; job <= active; job++) {
                func_801D4694(&marker_x, &marker_y, (u8)(i + 1), job);
                func_801D4030(marker_x, marker_y, 1);
            }
        }
    }

    func_801D4030(0x30, 0x4C, 2);
    buffer = g_UiTextFormatBuffer;
    sprintf((char*)buffer, D_801D0C10, D_801455C2);
    UI_TextDrawAscii(0x50, 0x4C, 0, buffer);
    UI_TextDraw(0x78, 0x4C, 0, 7, D_801D4C30);
    sprintf((char*)buffer, D_801D0C14, D_801455C4);
    UI_TextDrawAscii(0xB8, 0x4C, 0, buffer);
}

MATCH void func_801D3594(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D4030, 0xA8, 33, 20, 8);
}

/* Outlines the cell with its top and right edges, then its left and bottom, yellow when selected and blinking with the frame count otherwise. */
MATCH void func_801D36FC(s32 cell, s32 selected) {
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
        prim->x0 = D_801D4C44[cell_index].points[1][0];
    } else {
        prim->x0 = D_801D4C44[cell_index].points[0][0];
    }
    prim->y0 = D_801D4C44[cell_index].points[0][1];
    prim->x1 = D_801D4C44[cell_index].points[2][0];
    prim->y1 = D_801D4C44[cell_index].points[0][1];
    prim->x2 = D_801D4C44[cell_index].points[2][0];
    prim->y2 = D_801D4C44[cell_index].points[2][1];
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F3));

    prim = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(prim);
    if (cell_index != 0 && cell_index < COMMU_CELL_FRAME_COUNT && D_801F286D[g_GameAreaId] < cell_index) {
        prim->y0 = D_801D4C44[cell_index].points[0][1];
    } else {
        prim->y0 = D_801D4C44[cell_index].points[1][1];
    }
    prim->x0 = D_801D4C44[cell_index].points[1][0];
    prim->x1 = D_801D4C44[cell_index].points[1][0];
    prim->y1 = D_801D4C44[cell_index].points[2][1];
    prim->x2 = D_801D4C44[cell_index].points[2][0];
    prim->y2 = D_801D4C44[cell_index].points[2][1];
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F3));
}

MATCH void func_801D3984(s32 x, s32 y, s32 bright) {
    POLY_F3* poly;
    u8       colour;

    COMMU_DRAW_CURSOR_TRIANGLE(x, y, bright);
}

/* func_801D3A48 */
MATCH u8 Fairy_GetJobActive(u8 arg) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < FAIRY_JOB_COUNT; i++) {
        if (g_FairyJobs[i].active != 0) {
            if (g_FairyJobs[i].type == arg) {
                count++;
            }
        }
    }
    return count;
}

MATCH u8 func_801D3AA0(u8 type, u8 index) {
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

/* Steps the commu row cursor by the pad direction, holding the press state. */
MATCH void func_801D3B0C(u8* row) {
    s32 direction;

    direction = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown | PADLleft | PADLright));
    if (direction & PADLup) {
        switch (D_801D4DFC) {
            case 0:
                D_801D4DF8 = 1;
                D_801D4DFC = 1;
                *row       = D_801D4DF4 + 4;
                break;
            case 1:
                if (D_801D4DF8 == 0) {
                    D_801D4DFC = 0;
                    *row       = 0;
                } else {
                    D_801D4DF8 = 0;
                    *row       = *row - 4;
                }
                break;
            case 2:
                *row = *row - 1;
                if (*row < 9) {
                    *row = 0xB;
                }
                break;
        }
    } else if (direction & PADLdown) {
        switch (D_801D4DFC) {
            case 0:
                D_801D4DF8 = 0;
                D_801D4DFC = 1;
                *row       = D_801D4DF4;
                break;
            case 1:
                if (D_801D4DF8 != 0) {
                    D_801D4DFC = 0;
                    *row       = 0;
                } else {
                    D_801D4DF8 = 1;
                    *row       = *row + 4;
                }
                break;
            case 2:
                *row = *row + 1;
                if (*row >= 0xC) {
                    *row = 9;
                }
                break;
        }
    } else if (direction & PADLleft) {
        switch (D_801D4DFC) {
            case 0:
                D_801D4DFC = 2;
                *row       = 9;
                break;
            case 1:
                D_801D4DF4 = D_801D4DF4 - 1;
                *row       = *row - 1;
                if (D_801D4DF4 == 0) {
                    D_801D4DF4 = 1;
                    D_801D4DFC = 2;
                    *row       = D_801D4DF8 + 0xA;
                }
                break;
            case 2:
                if (*row == 9) {
                    D_801D4DFC = 0;
                    *row       = 0;
                } else {
                    D_801D4DFC = 1;
                    D_801D4DF8 = *row - 0xA;
                    *row       = (*row << 2) - 0x24;
                    D_801D4DF4 = 4;
                }
                break;
        }
    } else if (direction & PADLright) {
        switch (D_801D4DFC) {
            case 0:
                D_801D4DFC = 2;
                *row       = 9;
                break;
            case 1:
                D_801D4DF4 = D_801D4DF4 + 1;
                *row       = *row + 1;
                if (D_801D4DF4 >= 5) {
                    D_801D4DF4 = 4;
                    D_801D4DFC = 2;
                    *row       = D_801D4DF8 + 0xA;
                }
                break;
            case 2:
                if (*row == 9) {
                    D_801D4DFC = 0;
                    *row       = 0;
                } else {
                    D_801D4DFC = 1;
                    D_801D4DF4 = 1;
                    D_801D4DF8 = *row - 0xA;
                    *row       = (*row - 0xA) * 4 + 1;
                }
                break;
        }
    }
    if (direction & (PADLup | PADLdown | PADLleft | PADLright)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
}

/* Draws one type icon of the entry list. */
MATCH void func_801D3EFC(s16 x, s16 y, u8 ordinal) {
    s32      page;
    SPRT_16* sprite;
    u8       icon;

    page = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    GFX_SET_DRAW_MODE(page);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    sprite = GFX_CURSOR(SPRT_16);
    SetSprt16(sprite);
    setXY0(sprite, x, y);
    icon = ordinal;
    setUV0(sprite, (icon % 10) * 16 + 0x50 - (icon / 10) * 0x30, (icon / 10) * 16 - 0x20);
    sprite->clut = (D_801D4CD4[icon] >> 4) | 0x7840;
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_16));
}

/* Draws one tile of the entry screen's window frames. */
MATCH void func_801D4030(s16 x, s16 y, u8 piece) {
    s32   offset;
    s32   page;
    SPRT* sprite;

    page = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    GFX_SET_DRAW_MODE(page);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    offset = piece * 6;
    setXY0(sprite, x, y);
    setUV0(sprite, D_801D4CE0[offset], D_801D4CE0[offset + 1]);
    setWH(sprite, D_801D4CE0[offset + 2], D_801D4CE0[offset + 3]);
    sprite->clut = getClut(D_801D4CE0[offset + 4], D_801D4CE0[offset + 5] + 0x1E0);
    setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

/* Draws the entry list panel and its captions. */
MATCH void func_801D4178(s16 x, s16 y, u8 mode) {
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
    func_801D42DC((s16)x, (s16)(y - 1), span & 0xF0);
    i = 0;
    if (i < *count) {
        do {
            UI_TextDraw((s16)(x + 8), (s16)(y + 2 + i * 16), (mode * 7) & BYTE_MASK, 8, &D_801D4D34[i * 8]);
            i++;
        } while (i < D_801455C3);
    }
}

MATCH void func_801D42DC(s16 x, s16 y, u8 rows) {
    /* FAKE: retail frame reserves 8 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 8);
    s32 i;
    s32 offset;
    u8  count;

    func_801D4030(x, y, 6);
    for (i = 0; i < 8; i++) {
        offset = i * 8 + 8;
        func_801D4030((s16)(x + offset), y, 7);
        func_801D4030((s16)(x + offset), (s16)(y + rows), 0xC);
    }
    func_801D4030((s16)(x + 0x48), y, 8);
    count = (rows >> 3) - 1;
    i     = 0;
    if (count != 0) {
        do {
            offset = i * 8 + 8;
            func_801D4030(x, (s16)(y + offset), 9);
            func_801D4030((s16)(x + 0x48), (s16)(y + offset), 0xA);
            i++;
        } while (i < count);
    }
    func_801D4030(x, (s16)(y + rows), 0xB);
    func_801D4030((s16)(x + 0x48), (s16)(y + rows), 0xD);
}

MATCH s32 func_801D4474(void) {
    s32 val;
    u32 v;

    if (D_801D4DF8 == 0) {
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

/* Draws the panel of one commu type and returns its top. */
MATCH s16 func_801D44E0(s16 x, s16 y, u8 type, u8 mode) {
    s32 i;
    s32 height;
    s32 bottom;
    u16 span;
    u8  rows;

    rows   = D_801D4DD4[type].count;
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
    func_801D42DC((s16)x, (s16)(y - 1), span & 0xF0);
    i = 0;
    if (i < D_801D4DD4[type].count) {
        do {
            UI_TextDraw((s16)(x + 8), (s16)(y + 2 + i * 16), (mode * 7) & BYTE_MASK, 8, &D_801D4D34[0x50 + (D_801D4DD4[type].first + i) * 8]);
            i++;
        } while (i < D_801D4DD4[type].count);
    }
    return y;
}

/* Writes the screen origin of one entry-grid slot through the two pointers. */
MATCH void func_801D4694(s16* out_x, s16* out_y, s32 type, s32 ordinal) {
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
        sum_x  = x + D_801D4DDC[slot + (ordinal & BYTE_MASK)].x;
        *out_x = sum_x;
        sum_y  = y + D_801D4DDC[slot + (ordinal & BYTE_MASK)].y;
        *out_y = sum_y;
    } else {
        *out_x = x + 0xA;
        *out_y = y;
    }
}

MATCH void func_801D47C4(void) {
    D_801D4DF4 = D_801D4E00;
    D_801D4DF8 = D_801D4E04;
    D_801D4DFC = D_801D4E08;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
    D_801F294D--;
}

/* Commits the pending request into the fairy jobs and reports whether it went through. */
MATCH s32 func_801D482C(s32 ordinal_offset) {
    s32 committed;
    u8  slot;
    u8  step;
    u32 anchor;

    committed = 0;
    switch (D_801D4DFC) {
        case 1:
            if (Fairy_GetJobActive(D_801D4E28) == 3) {
                break;
            }
            if (D_801F286D[g_GameAreaId] < (s8)D_801D4E28) {
                break;
            }
        case 0:
        case 2:
            if ((s8)D_801D4E28 == g_SceneEventState.selection) {
                break;
            }
            D_801D4DF4                        = D_801D4E00;
            D_801D4DF8                        = D_801D4E04;
            D_801D4DFC                        = D_801D4E08;
            slot                              = func_801D3AA0(g_SceneEventState.selection, D_801D4E24 - ordinal_offset);
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

/* Publishes the text id of the row at the commu list cursor. */
MATCH void func_801D49C4(void) {
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
    } else if ((row & BYTE_MASK) >= 9) {
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
    D_801D4E0C = text_id;
}

/* Publishes the text id of the request row byte that room points at. */
MATCH void func_801D4AAC(u8* room) {
    u32 row;
    u32 limit;
    u8  room_type;
    s32 room_offset;
    u16 text_id;
    u16 row_text_id;

    row = *room;
    if (row == g_SceneEventState.selection) {
        text_id = 0x44;
    } else if (row == 0) {
        text_id = 0x69;
    } else if (row >= 9) {
        text_id = D_801D4DDA[row];
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
                row_text_id = D_801D4BB0[room_type];
            }
        }
        text_id = row_text_id;
    }
    D_801D4E0C = text_id;
}

MATCH void func_801D4B58(void) {
    D_801D4E10 = D_801F294D;
    D_801D4E14 = D_801D4E0C;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
    D_801D4E0C = 61;
    D_801D4E18 = 0;
    D_801F294D = 5;
}
