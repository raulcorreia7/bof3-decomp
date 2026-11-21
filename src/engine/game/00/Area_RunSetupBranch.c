#include "game_00.h"

/* Control records of the area setup stream. */
typedef enum AreaSetupControl {
    AREA_SETUP_CONTROL_IF                   = 0xF0, /* run the block when the area test holds */
    AREA_SETUP_CONTROL_IF_NOT               = 0xF1, /* run the block when the area test fails */
    AREA_SETUP_CONTROL_IF_CHAIN             = 0xF4, /* run the branch of the first test that holds */
    AREA_SETUP_CONTROL_CHAIN_END            = 0xF5, /* ends an if chain */
    AREA_SETUP_CONTROL_CHAIN_ELSE_IF        = 0xF6, /* next test of an if chain */
    AREA_SETUP_CONTROL_CHAIN_ELSE           = 0xF7, /* default branch of an if chain */
    AREA_SETUP_CONTROL_SET_SCENARIO_ID_BYTE = 0xF9, /* args: [id]; set D_8014820C to the byte */
    AREA_SETUP_CONTROL_SET_SCENARIO_ID      = 0xFA, /* set D_8014820C to the scenario id */
    AREA_SETUP_CONTROL_BLOCK_END            = 0xFE, /* ends an if block */
    AREA_SETUP_CONTROL_STREAM_END           = 0xFF, /* ends the stream */
} AreaSetupControl;

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
