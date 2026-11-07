#include "shop_00.h"

MATCH void func_801E2150(void) {
    s32 buttons;
    u16 pad;
    u8  next;
    u8  row;

    D_80148340 = 0x32;
    D_80148624 = 1;
    D_8014845A = 0;
    D_80148628 = D_80148358 + 4;
    D_8014862A = D_8014835A + (D_8014835F - D_8014835E) * 0xD + 0x1A;
    buttons    = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    row        = D_8014835F;
    if (buttons & PADLup) {
        if (row != 0) {
            D_8014835F = row - 1;
        }
        if (D_8014835F < D_8014835E) {
            D_8014835C = 0xF0;
        }
    } else if (buttons & PADLdown) {
        if (row < 16) {
            D_8014835F = row + 1;
        }
        if (D_8014835F >= D_8014835E + 9) {
            D_8014835C = 0x10;
        }
    } else if (buttons & PADL1) {
        if (D_8014835E == 0) {
            D_8014835F = 0;
        } else if (D_8014835E < 9) {
            D_8014835F -= D_8014835E;
            D_8014835E = 0;
        } else {
            D_8014835F -= 9;
            D_8014835E -= 9;
        }
    } else if (buttons & PADR1) {
        if (D_8014835E == 8) {
            D_8014835F = 0x10;
        } else {
            next       = row + 8;
            D_8014835F = next - D_8014835E;
            D_8014835E = 8;
        }
    }
    if (row != D_8014835F) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (D_8014835C == 0) {
        pad = g_InputPressed;
        if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (D_80148361 != GAME_NONE) {
                SND_PlayCue(EMI_CUE_ID(1, 3));
                SND_PlayCue(EMI_CUE_ID(1, 2));
                func_801E2724();
                D_80148357 = 3;
                D_80148624 = 0;
                D_80148654 = 8;
                D_80148652 += 1;
            } else {
                SND_PlayCue(EMI_CUE_ID(1, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            SND_PlayCue(EMI_CUE_ID(1, 2));
            D_80148333[0] = 1;
            D_80148357    = 1;
            D_80148624    = 0;
            D_80148654    = 0xA;
            D_80148652    = 0;
            D_80148651 += 1;
        }
    }
}
