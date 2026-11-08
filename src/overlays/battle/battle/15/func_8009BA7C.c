#include "battle_15.h"

MATCH void func_8009BA7C(void) {
    if (g_Battle.outcome.event_flags == 0) {
        g_Battle.phase.mode     = 5;
        g_AreaCameraStep        = 0;
        g_Battle.phase.step     = 3;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
        g_Battle.ui_state       = 0;
    }
}
