#include "game_00.h"

MATCH void func_801995A4(void) {
    g_MenuPanelStateHandlers[g_MenuCurrentPanel->state]();
    func_801999F8(g_MenuCurrentPanel);
}
