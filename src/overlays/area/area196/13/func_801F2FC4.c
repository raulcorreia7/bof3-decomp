#include "area196_13.h"

MATCH void func_801F2FC4(void) {
    SELF(Actor)->timer -= 4;
    if (SELF(Actor)->timer == 0) {
        Actor_Clear();
    }
    Game_SetCurrentActor(SELF(Actor)->timer);
}
