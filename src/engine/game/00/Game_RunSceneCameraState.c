#include "game_00.h"

MATCH void Game_RunSceneCameraState(void) {
    const Callback* entry;
    Callback        handler;

    entry = &g_GameFlowHandlers[g_GameEntrySubstate];
    /* FAKE: ORDER_LOCK is the macro spelling of the do/while (0) block that keeps this statement in place. */
    ORDER_LOCK((void)0);
    handler = *entry;
    handler();
}
