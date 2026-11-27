#include "engine/game/00/game_00.h"

/* The scenario handler `call` (+0x10): the optional handler this unit
 * belongs to (offsets +0x08/+0x0C carry its siblings, declared in
 * Area_IsStepBlocked.c and func_801A79A4.c). */

MATCH s8 Game_ScenarioCall(u16 handler_arg0, u16 handler_arg1) {
    Actor* saved;
    s8 (*handler)(s32 handler_arg0, s32 handler_arg1);
    s8 result;

    saved   = SELF(Actor);
    handler = g_ScenarioHandlers[g_ScenarioState.scenario_id]->call;
    result  = -1;
    if (handler != NULL) {
        result = handler(handler_arg0, handler_arg1);
    }
    if (result < 0) {
        result = Game_CallArea(handler_arg0, handler_arg1);
    } else {
        result = 1;
    }
    g_Self = saved;
    return result;
}
