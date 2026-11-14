#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E206C(void) {
    u16 sel;
    u16 bits;
    s32 i;
    s32 keys;

    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, 0x10, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801E26A8(0x1C, 0x40);
    func_801E2668(D_80148655, 0x70, 0x26);
    if ((s8)D_80148655 != 9) {
        WinDrawCueText(28, 19, ((s8)D_80148655 + 0xBC) & HALF_MASK);
    } else if (g_AutoRun != 0) {
        WinDrawCueText(28, 19, 0xCA);
    } else {
        WinDrawCueText(28, 19, 0xC5);
    }
    func_801E2D84(0xA8, 0x62);
    Menu_DrawCursorSprite(0xB0, (((s8)D_80148655 - 8) * 0x12 + 0x6A) & 0xFFFE, 0);
    sel = g_InputPressed & (PADRup | PADRdown | PADRleft | PADRright | PADL1 | PADR1);
    if (sel != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        g_InputMasks[INPUT_SLOT_SPEAK] &= ~(PADL2 | PADR2);
        g_InputMasks[INPUT_SLOT_CONFIRM] &= ~(PADL2 | PADR2);
        i = 0;
        while (!((sel >> i) & 1)) {
            i++;
            if (i >= 16) {
                break;
            }
        }
        if (i < 16) {
            do {
                sel &= ~(1 << i);
                i++;
            } while (i < 16);
        }
        for (i = 0; i < 6; i++) {
            if (g_InputMasks[D_801ECD14[i]] & sel) {
                break;
            }
        }
        if (i != 6) {
            g_InputMasks[D_801ECD14[i]] = g_InputMasks[D_801ECD0C[(s8)D_80148655]];
        }
        g_InputMasks[D_801ECD0C[(s8)D_80148655]] = sel;
        g_InputMasks[INPUT_SLOT_SPEAK] |= PADL2 | PADR2;
        g_InputMasks[INPUT_SLOT_CONFIRM] |= PADL2 | PADR2;
    }
    bits = g_InputPressed;
    keys = INPUT_GetRepeatedButtons(bits & INPUT_DIRECTIONAL);
    if (keys & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148655 = D_80148655 - 1;
        if ((s8)D_80148655 < 8) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
            D_80148655 = 0xD;
        }
    } else if (keys & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148655 = D_80148655 + 1;
        if ((s8)D_80148655 >= 0xE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
            D_80148655 = 8;
        }
    } else if (bits & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_80148655       = 7;
        g_MenuStep.state = g_MenuStep.state - 1;
    } else if (bits & PADstart) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_80148655       = 0;
        g_MenuStep.state = g_MenuStep.state - 2;
    }
}
#else
INCLUDE_ASM(func_801E206C);
#endif
