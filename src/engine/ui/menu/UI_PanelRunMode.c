#include "engine/game/00/game_00.h"

/* func_80199558 */
/* Runs the panel handler of the current task's mode. */
MATCH void UI_PanelRunMode(void) {
    u8 index;

    index = g_UIPanelCurrent->mode;
    g_UIPanelModes[index]();
}
