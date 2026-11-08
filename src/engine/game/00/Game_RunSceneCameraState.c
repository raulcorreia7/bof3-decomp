#include "game_00.h"

MATCH void Game_RunSceneCameraState(void) {
    const Callback* entry;
    Callback        handler;

    entry = &g_GameSceneCameraSubstates[g_GameEntrySubstate];
    /* FAKE: the order fence splits the schedule here. */
    FAKE_ORDER_FENCE();
    handler = *entry;
    handler();
}
