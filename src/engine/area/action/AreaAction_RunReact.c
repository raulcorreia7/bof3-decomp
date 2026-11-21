#include "engine/game/00/game_00.h"

/* func_801AD35C */
MATCH void AreaAction_RunReact(void) {
    Actor*   work        = g_Task;
    Callback handlers[2] = {AreaAction_React, AreaAction_End};

    handlers[work->unk_04]();
}
