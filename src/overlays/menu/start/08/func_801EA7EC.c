#include "start_08.h"

MATCH void func_801EA7EC(void) {
    g_MenuStartPanel18StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawEquipChoiceWindow(g_MenuCurrentPanel);
}
