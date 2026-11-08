#include "start_08.h"

/* func_801EA7EC */
MATCH void Menu_EquipChoicePanel(void) {
    g_MenuStartPanel18StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawEquipChoiceWindow(g_MenuCurrentPanel);
}
