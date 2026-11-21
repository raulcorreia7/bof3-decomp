#include "engine/game/00/game_00.h"

MATCH void Game_RunCampMenu(void) {
    const Callback* callbacks;

    g_GameEntryState    = 0u;
    g_GameEntrySubstate = 0u;
    SYS_ClearCurrentThread();
    UI_PanelResetTasks();

    while (1) {
        callbacks = g_GameCampMenuLoad;
        SYS_ThreadWait(1u);
        callbacks[g_GameEntryState]();
        UI_PanelUpdateTasks();
    }
}
