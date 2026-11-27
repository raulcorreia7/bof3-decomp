#include "engine/game/00/game_00.h"

MATCH void Game_SceneCameraUpdate(void) {
    Callback* entry;
    Callback  handler;

    entry   = &g_GameSceneCameraSteps[g_GameEntrySubstate];
    handler = *entry;
    handler();
}
