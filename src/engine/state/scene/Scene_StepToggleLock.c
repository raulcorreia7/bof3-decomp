#include "engine/game/00/game_00.h"

/* func_8019AB5C */
/* Counts its timer down, then clears scene flag 28 and frees the actor. */
MATCH void Scene_StepToggleLock(void) {
    Actor* work;
    u8     value;

    work  = TASK(Actor);
    value = work->timer;
    if (value == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 28u);
        Actor_Clear();
        return;
    }
    work->timer = (value - 1);
}
