#include "engine/game/00/game_00.h"

/* func_801A4400 */
/* Runs one control record 0xF0 to 0xFA. */
MATCH u8* Area_RunSetupBranch(u8* script) {
    u8 value;

    switch (script[0]) {
        case AREA_SETUP_CONTROL_IF:
            script = ((u8 * (*)(u8*)) Area_RunSetupIf)(script + 1);
            break;
        case AREA_SETUP_CONTROL_IF_NOT:
            script = ((u8 * (*)(u8*)) Area_RunSetupIfNot)(script + 1);
            break;
        case AREA_SETUP_CONTROL_IF_CHAIN:
            script = Area_RunSetupIfChain(script + 1);
            break;
        case AREA_SETUP_CONTROL_SET_SCENARIO_ID_BYTE:
            value = script[1];
            script += 2;
            (*(s16*)&D_8014820C) = value;
            break;
        case AREA_SETUP_CONTROL_SET_SCENARIO_ID:
            value = g_ScenarioState.scenario_id;
            script += 1;
            (*(s16*)&D_8014820C) = (s8)value;
            break;
    }
    return script;
}
