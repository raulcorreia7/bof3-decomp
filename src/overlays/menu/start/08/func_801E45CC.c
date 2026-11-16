#include "start_08.h"

void Menu_DrawBackdrop(void);

MATCH void func_801E45CC(void) {
    if (WINDOW_EFFECT_IDLE()) {
        g_MenuStartStep     = 0;
        g_GameEntrySubstate = D_801ED7EC ? 2 : 3;
    } else {
        Menu_DrawBackdrop();
        func_801E6D88(0);
    }
}
