#include "engine/game/00/game_00.h"

/* func_801B5884 */
/* Starts the camera look state on the view button; true when requested. */
MATCH bool Game_CameraLookRequest(void) {
    if (!(g_Game.flags & 0x2000) && (g_Game.input & g_InputMasks[FIELD_INPUT_VIEW])) {
        g_GameStateIndex = GAME_REQUEST_CAMERA_LOOK;
        Actor_RequestRoute(SELF(Actor)->direction);
        SELF(Actor)->header.mode = 1;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
