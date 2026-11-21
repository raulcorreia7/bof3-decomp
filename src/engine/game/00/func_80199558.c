#include "game_00.h"

MATCH void func_80199558(void) {
    u8 index;

    index = g_UiPanelCurrent->mode;
    g_UiPanelModes[index]();
}
