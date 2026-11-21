#include "engine/game/00/game_00.h"

/* func_801AD9C4 */
MATCH void FieldAction_WaitMessageFade(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }

    g_Task->unk_04 = 5;
}
