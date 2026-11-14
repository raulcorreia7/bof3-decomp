#include "game_00.h"

MATCH void Game_UpdateCampMenu(void) {
    const Callback* callbacks;

    g_GameEntryState    = 0u;
    g_GameEntrySubstate = 0u;
    func_8014BA04();
    Menu_ResetPanelTasks();

    while (1) {
        callbacks = g_GameCampMenuLoad;
        SYS_ThreadWait(1u);
        callbacks[g_GameEntryState]();
        Menu_UpdatePanelTasks();
    }
}
