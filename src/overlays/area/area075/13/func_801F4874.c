#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4874(void) {
    u8  shown;
    u8  blink;
    u8* buffer;
    u8  tens;
    u8  ones;

    if (D_801F58C6 & 4) {
        shown = (g_FrameCount & 0xC) != 0;
    } else {
        shown = 1;
    }
    blink = (abs(D_801F58CA - D_801F58CC) >= 0x97) << 1;
    if ((D_801F58C6 & 1) == 0) {
        tens = D_801F58CA / 100;
        ones = D_801F58CA % 100;
        UI_WindowDrawPanel(0x18, 0x20, 0x54, 0x11, 0);
        buffer = g_UiTextFormatBuffer;
        sprintf((char*)buffer, (char*)D_801F2C94, (u8)tens, (u8)ones);
        buffer[2] = 0x3E;
        if (shown) {
            UI_TextDraw(0x2A, 0x22, blink, 6, buffer);
        }
        tens = D_801F58CC / 100;
        ones = D_801F58CC % 100;
        UI_WindowDrawPanel(0x90, 0x20, 0x54, 0x11, 0);
        sprintf((char*)buffer, (char*)D_801F2C94, (u8)tens, (u8)ones);
        g_UiTextFormatBuffer[2] = 0x3E;
        if (shown) {
            UI_TextDraw(0xA2, 0x22, blink, 6, buffer);
        }
    }
}
#else
INCLUDE_ASM(func_801F4874);
#endif
