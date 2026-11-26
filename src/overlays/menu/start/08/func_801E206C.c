#include "start_08.h"

#ifdef NON_MATCHING
/* Settings screen: draws the option rows and rebinds a pressed button to its input slot. */
NON_MATCHING void func_801E206C(void) {
    u8* cursor;
    s32 cue;
    u16 buttons; /* the pressed actions, reduced to the first one */
    u16 scan;    /* the pressed actions, scanned for the first one */
    s32 i;
    s32 keys;

    Menu_DrawClutStrip(g_WindowClut);
    Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    func_801E26A8(0x1C, 0x40);
    cursor = &D_80148655;
    func_801E2668(*cursor, 0x70, 0x26);
    cue = (s8)*cursor;
    if (cue != 9) {
        cue += 0xBC;
        cue = (u16)cue;
    } else if (g_AutoRun == 0) {
        cue = 0xC5;
    } else {
        cue = 0xCA;
    }
    WinDrawCueText(28, 19, cue);
    func_801E2D84(0xA8, 0x62);
    UI_CursorDraw(0xB0, (((s8)D_80148655 - 8) * 0x12 + 0x6A) & 0xFFFE, 0);
    buttons = g_PadStates[0].pressed & (PADRup | PADRdown | PADRleft | PADRright | PADL1 | PADR1);
    scan    = buttons;
    if (buttons != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        g_InputMasks[INPUT_SLOT_SPEAK] &= ~(PADL2 | PADR2);
        g_InputMasks[INPUT_SLOT_CONFIRM] &= ~(PADL2 | PADR2);
        for (i = 0; i < 16; i++) {
            if ((scan >> i) & 1) {
                i += 1;
                break;
            }
        }
        for (; i < 16; i++) {
            buttons &= ~(1 << i);
        }
        for (i = 0; i < 6; i++) {
            if (g_InputMasks[D_801ECD14[i]] & buttons) {
                break;
            }
        }
        if (i != 6) {
            g_InputMasks[D_801ECD14[i]] = g_InputMasks[D_801ECD0C[(s8)D_80148655]];
        }
        g_InputMasks[D_801ECD0C[(s8)D_80148655]] = buttons;
        g_InputMasks[INPUT_SLOT_SPEAK] |= PADL2 | PADR2;
        g_InputMasks[INPUT_SLOT_CONFIRM] |= PADL2 | PADR2;
    }
    keys = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if (keys & PADLup) {
        cursor = &D_80148655;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        *cursor = *cursor - 1;
        if ((s8)*cursor < 8) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            *cursor = 0xD;
        }
    } else if (keys & PADLdown) {
        cursor = &D_80148655;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        *cursor = *cursor + 1;
        if ((s8)*cursor >= 0xE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
            *cursor = 8;
        }
    } else if (g_PadStates[0].pressed & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        D_80148655 = 7;
        D_80148652 = D_80148652 - 1;
    } else if (g_PadStates[0].pressed & PADstart) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80148655 = 0;
        D_80148652 = D_80148652 - 2;
    }
}
#else
INCLUDE_ASM(func_801E206C);
#endif
