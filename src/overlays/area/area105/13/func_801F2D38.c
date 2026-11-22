#include "area105_13.h"

MATCH void func_801F2D38(void) {
    TASK(Actor)->timer++;
    if (g_AreaSceneMode == 0) {
        Actor_Clear();
    }
    func_801F2D9C(TASK(Actor)->timer);
}
