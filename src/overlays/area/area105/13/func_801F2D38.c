#include "area105_13.h"
#include "area/spad.h"

MATCH void func_801F2D38(void) {
    g_Task->timer++;
    if (g_AreaSceneMode == 0) {
        Actor_Clear();
    }
    func_801F2D9C(g_Task->timer);
}
