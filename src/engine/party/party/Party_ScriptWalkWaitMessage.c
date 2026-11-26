#include "engine/game/00/game_00.h"

/* func_801B6FDC */
/* Waits for the message window to close. */
MATCH void Party_ScriptWalkWaitMessage(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    g_Game.current->u.field.flags &= 0xDFu;
    SELF(Actor)->unk_03 = 0;
}
