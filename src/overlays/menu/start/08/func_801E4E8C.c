#include "start_08.h"

MATCH void func_801E4E8C(void) {
    if (WINDOW_EFFECT_IDLE()) {
        g_MenuStartStep     = 0;
        g_GameEntrySubstate = 4;
    } else {
        func_801E7000();
    }
}
