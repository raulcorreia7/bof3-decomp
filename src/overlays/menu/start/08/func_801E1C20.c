#include "start_08.h"

/* Settings list: draws the selected row, applies the row's toggle, then moves
 * the selection. */
MATCH void func_801E1C20(void) {
    u8*  selection;
    u8*  option;
    u8*  timer;
    u8*  step;
    u16* pad;
    u8   next;
    s32  input;

    selection = &D_80148655;
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 19, (u16)((s8)*selection + 0xBC));
    func_801E26A8(0x1C, 0x40);
    func_801E2668(*selection, 0x70, 0x26);
    switch ((s8)*selection - 2) {
        case 0:
            if (g_InputPressed & PADLright) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &D_80144950;
                next    = *option + 1;
                *option = next;
                if ((s8)next >= 3) {
                    *option = 0;
                }
            } else if (g_InputPressed & PADLleft) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &D_80144950;
                next    = *option - 1;
                *option = next;
                if ((s8)next < 0) {
                    *option = 2;
                }
            }
            break;
        case 1:
            if (g_InputPressed & PADLright) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &g_WindowStyle;
                next    = *option + 1;
                *option = next;
                if ((s8)next >= 4) {
                    *option = 0;
                }
            } else if (g_InputPressed & PADLleft) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &g_WindowStyle;
                next    = *option - 1;
                *option = next;
                if ((s8)next < 0) {
                    *option = 3;
                }
            }
            break;
        case 2:
            if (g_InputPressed & PADLleft) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &D_80144953;
                next    = *option - 1;
                *option = next;
                if ((s8)next < 0) {
                    *option = 3;
                }
            } else if (g_InputPressed & PADLright) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &D_80144953;
                next    = *option + 1;
                *option = next;
                if ((s8)next >= 4) {
                    *option = 0;
                }
            }
            break;
        case 3:
            if (g_InputPressed & (PADLright | PADLleft)) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &g_SndMono_nv;
                next    = *option ^ 1;
                *option = next;
                if (next == 0) {
                    SsSetStereo();
                } else {
                    SsSetMono();
                }
            }
            break;
        case 4:
            if (g_InputPressed & (PADLright | PADLleft)) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                option  = &g_AutoRun;
                next    = *option ^ 1;
                *option = next;
            }
            break;
        case 5:
            if (g_InputPressed & (g_InputMasks[MENU_INPUT_CONFIRM] | PADLright | PADLleft)) {
                SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 1));
                D_80148655 = 8;
                D_80148652++;
                return;
            }
            break;
    }
    pad   = &g_InputPressed;
    input = INPUT_REPEATED(*pad, INPUT_DIRECTIONAL);
    if (input & PADLup) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148654 = 0;
        D_80148655--;
        if ((s8)D_80148655 < 2) {
            D_80148655 = 0;
            D_80148652--;
        }
    } else if (input & PADLdown) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148654 = 0;
        D_80148655++;
        if ((s8)D_80148655 >= 8) {
            D_80148655 = 0;
            D_80148652--;
        }
    } else if (*pad & (g_InputMasks[MENU_INPUT_CANCEL] | PADstart)) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 6));
        step       = &D_80148652;
        D_80148655 = 0;
        (*step)--;
    }
    timer = &D_80148654;
    if (*timer < 3) {
        (*timer)++;
    }
}
