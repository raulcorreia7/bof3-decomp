#include "start_08.h"

MATCH void func_801D8DC8(void) {
    u8* panel;
    s32 buttons;
    u8  old;
    u8  column;
    s32 next;

    Menu_DrawClutStrip(D_80144953);
    panel = &D_80148594;
    if (D_801485A0 != 0) {
        D_801484CC = D_801485A0 + 0x4183;
    } else {
        D_801484CC = 0;
    }
    D_80148624 = 1;
    D_80148628 = *(u16*)(panel + 4) + 7;
    D_8014862A = *(u16*)(panel + 6) + ((panel[0xB] - panel[0xA]) * 0xD + 0x1A);
    buttons    = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
    old        = panel[0xB];
    if (buttons & PADLup) {
        if (old != 0) {
            panel[0xB] = old - 1;
        }
        if (panel[0xB] < panel[0xA]) {
            panel[8] = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (old < 0x11) {
            panel[0xB] = old + 1;
        }
        if (panel[0xB] >= panel[0xA] + 9) {
            panel[8] = 0x10;
        }
    } else if (buttons & PADL1) {
        column = panel[0xA];
        if (column == 0) {
            panel[0xB] = 0;
        } else if (column < 9) {
            panel[0xB] = old - column;
            panel[0xA] = 0;
        } else {
            panel[0xB] = old - 9;
            panel[0xA] = panel[0xA] - 9;
        }
    } else if (buttons & PADR1) {
        if (panel[0xA] == 9) {
            panel[0xB] = 0x11;
        } else if (panel[0xA] != 0) {
            next       = old + 9;
            panel[0xB] = next - panel[0xA];
            panel[0xA] = 9;
        } else {
            panel[0xB] = old + 9;
            panel[0xA] = panel[0xA] + 9;
        }
    }
    D_801ED891 = g_BattleListCursor;
    D_801ED890 = D_8014859E;
    if (old != panel[0xB]) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148597 = 1;
        D_80148624 = 0;
        D_80148654 = 7;
        D_80148652 += 1;
    }
}
