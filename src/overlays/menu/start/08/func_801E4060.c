#include "start_08.h"

void Menu_DrawBackdrop(void);

MATCH void func_801E4060(void) {
    Menu_DrawBackdrop();
    D_80148654 = 2;
    g_MenuCampStep += 1;
}
