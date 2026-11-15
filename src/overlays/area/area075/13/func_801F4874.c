#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4874(void) {
    u8  shown;
    s32 blink;

    if (D_801F58C6 & 4) {
        shown = (g_FrameCount & 0xC) != 0;
    } else {
        shown = 1;
    }
    blink = (abs(D_801F58CA - D_801F58CC) >= 0x97) << 1;
    if ((D_801F58C6 & 1) == 0) {
        func_801F4A50(0x18, 0x20, 0x54, 0x11, 0);
        sprintf(g_UiFormatBuffer, (char*)D_801F2C94, (u8)(D_801F58CA / 100), (u8)(D_801F58CA % 100));
        g_UiFormatBuffer[2] = 0x3E;
        if (shown) {
            UI_DrawText(0x2A, 0x22, blink, 6, g_UiFormatBuffer);
        }
        func_801F4A50(0x90, 0x20, 0x54, 0x11, 0);
        sprintf(g_UiFormatBuffer, (char*)D_801F2C94, (u8)(D_801F58CC / 100), (u8)(D_801F58CC % 100));
        g_UiFormatBuffer[2] = 0x3E;
        if (shown) {
            UI_DrawText(0xA2, 0x22, blink, 6, g_UiFormatBuffer);
        }
    }
}
#else
INCLUDE_ASM(func_801F4874);
#endif
