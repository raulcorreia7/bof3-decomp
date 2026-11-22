#include "battle_15.h"

/* func_8009BA7C */
MATCH void Battle_EndEscape(void) {
    if (g_Battle.outcome.event_flags == 0) {
        g_Battle.phase.mode     = BATTLE_MODE_RESULT;
        g_AreaCameraSpeed       = 0;
        g_Battle.phase.step     = 3;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
        g_Battle.ui_mode        = 0;
    }
}
