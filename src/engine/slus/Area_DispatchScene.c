#include "engine/slus/slus.h"

/* installs the mode work area and dispatches through the D_80183A60 table. */
MATCH void Area_DispatchScene(void) {
    g_Task      = D_8014626C;
    g_GameState = g_Game.members;
    D_8014625C  = g_InputHeld;
    ((void (*)(void))D_80183A60[D_8014626D])();
}
