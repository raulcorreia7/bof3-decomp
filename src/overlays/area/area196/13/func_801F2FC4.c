#include "area196_13.h"

MATCH void func_801F2FC4(void) {
    TASK(Actor)->timer -= 4;
    if (TASK(Actor)->timer == 0) {
        Actor_Clear();
    }
    Game_SetCurrentActor(TASK(Actor)->timer);
}
