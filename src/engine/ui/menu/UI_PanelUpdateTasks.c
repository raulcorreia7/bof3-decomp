#include "engine/slus/slus.h"

/* copies the nine menu-panel handlers to the stack, then dispatches
 * active panel tasks whose mode is at or above the current menu mode.
 */
MATCH void UI_PanelUpdateTasks(void) {
    MenuPanelFuncs handlers;
    Callback*      funcs;
    u8*            taskBase;
    u8*            task;
    s32            mode;
    s32            i;
    s32            offset;

    handlers = g_UIPanels;
    mode     = g_UIPanelMode;
    if (mode < 3) {
        funcs    = handlers.handlers;
        taskBase = (u8*)g_UIPanelTasks;
        i        = 0;
        do {
            task   = taskBase;
            offset = 0;
            do {
                if ((((u8*)g_UIPanelTasks)[offset] != 0) && (*((u8*)&g_UIPanelTasks[0].layer + offset) == mode)) {
                    g_UIPanelCurrent = (MenuPanelTask*)task;
                    funcs[task[1]]();
                }
                task += sizeof(MenuPanelTask);
                i++;
                offset += sizeof(MenuPanelTask);
            } while (i < 22);
            mode++;
            i = 0;
        } while (mode < 3);
    }
}
