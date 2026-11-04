#include "engine/slus/slus.h"

/* copies the nine menu-panel handlers to the stack, then dispatches
 * active panel tasks whose mode is at or above the current menu mode.
 */
MATCH void Menu_RunPanelTasks(void) {
    MenuPanelFuncs handlers;
    Callback*      funcs;
    u8*            taskBase;
    u8*            task;
    s32            mode;
    s32            i;
    s32            offset;

    handlers = g_MenuPanels;
    mode     = g_MenuPanelMode;
    if (mode < 3) {
        funcs    = handlers.handlers;
        taskBase = (u8*)g_MenuPanelTasks;
        i        = 0;
        do {
            task   = taskBase;
            offset = 0;
            do {
                if ((((u8*)g_MenuPanelTasks)[offset] != 0) && (*((u8*)&D_8014833F + offset) == mode)) {
                    g_MenuPanelTaskCurrent = (MenuPanelTask*)task;
                    funcs[task[1]]();
                }
                task += 0x24;
                i++;
                offset += 0x24;
            } while (i < 22);
            mode++;
            i = 0;
        } while (mode < 3);
    }
}
