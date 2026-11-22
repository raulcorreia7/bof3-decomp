#include "area196_13.h"

MATCH void func_801F2CA4(void) {
    if (g_AreaSceneMode == 1) {
        TASK(Actor)->header.step += 1;
    }
    Game_SetCurrentActor(0);
}
