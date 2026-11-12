#include "commu01_07.h"

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

INCLUDE_ASM(func_801D0CAC);

MATCH void func_801D0E44(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Funcs, D_801D4E08);
}

MATCH void func_801D0E80(void) {
    SYS_DISPATCH_BYTE(D_801D4BE4, D_801F294D);
}

INCLUDE_ASM(func_801D0EBC);

INCLUDE_ASM(func_801D1158);

MATCH void func_801D1328(void) {
    SYS_DISPATCH_BYTE(g_Commu01Step2Sub1Funcs, D_801F294D);
}

/* Reads the fairy room list input and draws the selected room. */
MATCH void func_801D1364(void) {
    u16 x;
    s16 y;
    u8* selection;
    u8  old_row;
    s8  row;
    u8  count;
    s32 room;
    u16 buttons;

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_801D4E0C = 0xB5;
        D_801F294C--;
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        row = D_801D4E24;
        if (row != 0) {
            D_801D4E0C = 0x44;
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
        count   = func_801D3A48(g_SceneEventSelection);
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
            D_801D4E0C = 0xB5;
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

INCLUDE_ASM(func_801D1778);

INCLUDE_ASM(func_801D1A94);

INCLUDE_ASM(func_801D1E48);

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

/* Outlines cell with a top line and a left line, white when selected is set and blinking otherwise. */
MATCH void func_801D36FC(s32 cell, s32 selected) {
    LINE_F3* prim;
    s32      shade;
    s32      state;
    u8       cell_index;

    cell_index = cell;
    if ((selected & BYTE_MASK) == 0) {
        state = g_FrameCount;
        if (state & 8) {
            shade = (state & 6) << 5 | 0x3F;
        } else {
            shade = (~state & 6) << 5 | 0x3F;
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

INCLUDE_ASM(func_801D3984);

MATCH u8 func_801D3A48(u8 arg) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x3C; i++) {
        if (g_FairyJobs[i].active != 0) {
            if (g_FairyJobs[i].type == arg) {
                count++;
            }
        }
    }
    return count;
}

INCLUDE_ASM(func_801D3AA0);

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
