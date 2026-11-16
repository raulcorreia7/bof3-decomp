#include "start_08.h"

void Menu_DrawBackdrop(void);

MATCH void func_801E40A0(void) {
    u8* timer;

    Menu_DrawBackdrop();
    WinDrawCueText(70, 190, 0xA8);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        g_MenuStartStep++;
    }
}
