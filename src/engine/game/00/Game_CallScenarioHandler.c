#include "game_00.h"

/* Scene view entry at view offset +0x10: the optional handler this unit
 * belongs to (offsets +0x08/+0x0C carry its siblings, declared in
 * Area_IsStepBlocked.c and func_801A79A4.c). */

MATCH s8 Game_CallScenarioHandler(u16 handler_arg0, u16 handler_arg1) {
    Actor* saved;
    s8 (*handler)(s32 handler_arg0, s32 handler_arg1);
    s8 result;

    saved   = g_SpadWork;
    handler = g_SceneScenes[(s32)g_SceneState.scenario_id]->entry_10;
    result  = -1;
    if (handler != NULL) {
        result = handler(handler_arg0, handler_arg1);
    }
    if (result < 0) {
        result = func_801A8CB4(handler_arg0, handler_arg1);
    } else {
        result = 1;
    }
    g_SpadWork = saved;
    return result;
}
