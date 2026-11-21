#include "engine/game/00/game_00.h"

/* func_801AD35C */
MATCH void FieldAction_RunReact(void) {
    Actor*   work        = g_Task;
    Callback handlers[2] = {FieldAction_React, FieldAction_End};

    handlers[work->unk_04]();
}
