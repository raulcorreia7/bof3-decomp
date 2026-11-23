#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4874(void) {
    u8    shown;
    s32   blink;
    u8*   buffer;
    char* format;

    if (D_801F58C6 & 4) {
        shown = (g_FrameCount & 0xC) != 0;
    } else {
        shown = 1;
    }
    blink  = (abs(D_801F58CA - D_801F58CC) >= 0x97) << 1;
    format = (char*)D_801F2C94;
    if ((D_801F58C6 & 1) == 0) {
        UI_WindowDrawPanel(0x18, 0x20, 0x54, 0x11, 0);
        buffer = g_UiTextFormatBuffer;
        sprintf((char*)buffer, format, (u8)(D_801F58CA / 100), (u8)(D_801F58CA % 100));
        buffer[2] = 0x3E;
        if (shown) {
            UI_TextDraw(0x2A, 0x22, blink, 6, buffer);
        }
        UI_WindowDrawPanel(0x90, 0x20, 0x54, 0x11, 0);
        sprintf((char*)buffer, format, (u8)(D_801F58CC / 100), (u8)(D_801F58CC % 100));
        buffer[2] = 0x3E;
        if (shown) {
            UI_TextDraw(0xA2, 0x22, blink, 6, buffer);
        }
    }
}
#else
INCLUDE_ASM(func_801F4874);
#endif
