#include "commu01_07.h"
#include "overlays/commu/Commu_CursorTriangle.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu01 overlay entry: the shared commu step byte selects the handler. */
MATCH void func_801D0C2C(void) {
    SYS_DISPATCH_BYTE(g_Commu01States, D_801F294C);
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
    u8  mode;

    pad = g_InputPressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        D_801D4E0C = 0xFFFF;
        ((u8*)&g_SceneEventStep)[0]++;
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
                if (Fairy_GetJobActive(g_SceneEventSelection) != 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                    func_801D49C4();
                    D_801F294C++;
                } else {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case 1:
                if (D_801F286D[g_GameAreaId] < g_SceneEventSelection) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                } else {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                    func_801D49C4();
                    D_801F294C++;
                }
                break;
            default:
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                break;
        }
    } else {
        func_801D3B0C(&g_SceneEventSelection);
    }
    func_801D3038();
    func_801D36FC(g_SceneEventSelection, 0);
}

MATCH void func_801D0E44(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Funcs, D_801D4E08);
}

MATCH void func_801D0E80(void) {
    SYS_DISPATCH_BYTE(D_801D4BE4, D_801F294D);
}

/* Moves the ordinal of the selected record kind and draws its cell. */
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

    pad_word = &g_InputPressed;
    pad      = *pad_word;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = 0xB5;
        D_801F294C--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        D_801D4E0C = 0x44;
        D_801D4E28 = g_SceneEventSelection;
        D_801F294D++;
    } else {
        count     = Fairy_GetJobActive(g_SceneEventSelection);
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
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        }
    }
    func_801D3038();
    row = &g_SceneEventSelection;
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

    pad       = g_InputPressed;
    committed = 0;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
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
    row = &g_SceneEventSelection;
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
        func_801D28A4(0xA0, 0x3E, func_801D3AA0(g_SceneEventSelection, D_801D4E24), 1);
    }
}

MATCH void func_801D1328(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Sub1Funcs, D_801F294D);
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

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = 181;
        D_801F294C--;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        row = D_801D4E24;
        if (row != 0) {
            D_801D4E0C = 68;
            D_801D4E28 = g_SceneEventSelection;
            D_801F294D++;
        } else {
            room = g_SceneEventSelection - 1;
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
        buttons = INPUT_REPEATED(g_InputPressed, (PADLright | PADLleft));
        old_row = D_801D4E24;
        count   = Fairy_GetJobActive(g_SceneEventSelection);
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
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        }
    }

    func_801D3038();
    selection = &g_SceneEventSelection;
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
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        func_801D47C4();
        func_801D49C4();
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        result = func_801D482C(1);
        if (result & BYTE_MASK) {
            D_801D4E0C = 181;
        }
    } else {
        func_801D3B0C(&D_801D4E28);
        func_801D4AAC(&D_801D4E28);
    }
    func_801D3038();
    selection = &g_SceneEventSelection;
    func_801D36FC(*selection, 1);
    func_801D36FC(D_801D4E28, 0);
    if (!(result & BYTE_MASK)) {
        func_801D4694(&x, &y, *selection, D_801D4E24);
        func_801D3984((s16)(x + 4), y, 1);
        func_801D28A4(0xA0, 0x3E, func_801D3AA0(*selection, (D_801D4E24 - 1) & BYTE_MASK) & BYTE_MASK, 1);
    }
}

/* Moves the request row between kinds and draws the chosen kind. */
MATCH void func_801D1778(void) {
    u16 pad;
    s32 direction;
    u8  row;
    u8* cursor;
    u8  kind;
    u8  next;
    s32 rooms_offset;
    s8  srow;
    s16 x;
    s16 y;

    pad = g_InputPressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        func_801D49C4();
        D_801F294D = 0;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        srow = D_801D4E28;
        kind = D_801D4C04[srow];
        if (kind == 0xFF) {
            func_801D4B58();
        } else {
            rooms_offset = (g_SceneEventSelection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E2C = g_FairyRooms[rooms_offset + 1];
            } else {
                D_801D4E2C = 0;
            }
            srow       = D_801D4E28;
            D_801D4E1C = D_801D4C04[srow];
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
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
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        }
        srow       = D_801D4E28;
        D_801D4E0C = D_801D4BB8[srow];
    }
    func_801D3038();
    cursor = &g_SceneEventSelection;
    func_801D36FC(*cursor, 1);
    func_801D4694(&x, &y, *cursor, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    func_801D4178((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 0);
    Menu_DrawCursorSprite((u16)((52 * ((*cursor - 1) % 4) + 0x44) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E28 * 16), 0);
}

/* Moves the request line inside the chosen kind and draws its grid. */
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

    pad = g_InputPressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801D4E1C = 0xFF;
        D_801F294D--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (D_801D4C18[D_801D4E1C][1] == 0xFF) {
            func_801D4B58();
        } else {
            srow         = D_801D4E28;
            rooms_offset = (g_SceneEventSelection - 1) * 8;
            if (srow == g_FairyRooms[rooms_offset] - 4) {
                D_801D4E30 = g_FairyRooms[rooms_offset + 2];
            } else {
                D_801D4E30 = 0;
            }
            D_801D4E20 = D_801D4C18[D_801D4E1C][1];
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
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
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        }
    }
    func_801D3038();
    cursor = &g_SceneEventSelection;
    func_801D36FC(*cursor, 1);
    func_801D4694(&x, &y, *cursor, 0);
    func_801D3984(x, y, 1);
    y = func_801D4474();
    func_801D4178((s16)(52 * ((*cursor - 1) % 4) + 0x42), y, 1);
    if (D_801D4E1C != 0xFF) {
        y = y + (12 + 16 * (s8)D_801D4E28);
        y = func_801D44E0((s16)(52 * ((*cursor - 1) % 4) + 0x4A), y, D_801D4E1C, 0);
        Menu_DrawCursorSprite((u16)((52 * ((*cursor - 1) % 4) + 0x4C) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E2C * 16), 0);
    }
}

/* Toggles the request pair and draws both kind grids. */
MATCH void func_801D1E48(void) {
    u16 pad;
    s32 direction;
    u8* row;
    s16 x;
    s16 y;

    pad = g_InputPressed;
    if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = 0x45;
        D_801D4E20 = 0xFF;
        D_801F294D--;
    } else if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        func_801D4B58();
    } else {
        direction = INPUT_REPEATED(pad, (PADLup | PADLdown));
        if (direction & (PADLup | PADLdown)) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
            D_801D4E30 ^= 1;
        }
    }
    func_801D3038();
    row = &g_SceneEventSelection;
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
        Menu_DrawCursorSprite((u16)((52 * ((*row - 1) % 4) + 0x54) & 0xFFFC), (u16)(y + 4 + (s8)D_801D4E30 * 16), 0);
    }
}

INCLUDE_ASM(func_801D2110);

#include "overlays/commu/Commu_CellGrid.h"

MATCH void func_801D273C(s16 x, s16 y) {
    s32 i;
    s32 offset;

    COMMU_DRAW_CELL_GRID(func_801D4030, 0x22, 7, 4, 6);
}

INCLUDE_ASM(func_801D28A4);

INCLUDE_ASM(func_801D2D98);

INCLUDE_ASM(func_801D3038);

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
    GFX_AddPrim(1, sizeof(LINE_F3));

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
    GFX_AddPrim(1, sizeof(LINE_F3));
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

INCLUDE_ASM(func_801D3B0C);

INCLUDE_ASM(func_801D3EFC);

INCLUDE_ASM(func_801D4030);

INCLUDE_ASM(func_801D4178);

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

INCLUDE_ASM(func_801D44E0);

INCLUDE_ASM(func_801D4694);

MATCH void func_801D47C4(void) {
    D_801D4DF4 = D_801D4E00;
    D_801D4DF8 = D_801D4E04;
    D_801D4DFC = D_801D4E08;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    D_801F294D--;
}

INCLUDE_ASM(func_801D482C);

INCLUDE_ASM(func_801D49C4);

INCLUDE_ASM(func_801D4AAC);

MATCH void func_801D4B58(void) {
    D_801D4E10 = D_801F294D;
    D_801D4E14 = D_801D4E0C;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
    D_801D4E0C = 61;
    D_801D4E18 = 0;
    D_801F294D = 5;
}
