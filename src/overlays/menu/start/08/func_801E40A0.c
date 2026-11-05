#include "start_08.h"

void func_801E7608(void);

MATCH void func_801E40A0(void) {
    u8* timer;

    func_801E7608();
    WinDrawCueText(70, 190, 0xA8);
    timer = &D_80148654;
    if (TIMER_EXPIRED(*timer)) {
        g_MenuStartStep++;
    }
}
