#include "engine/game/00/game_00.h"

/* func_801A3F3C */
/* Runs the setup stream records until the end byte. */
MATCH void Area_RunSetupRecords(u8* script) {
    u16 op;

    D_8014820C = (s8)g_ScenarioState.scenario_id;
    op         = *script;
    while ((u8)op != GAME_NONE) {
        if (op < 0xF0U) {
            script = ((u8 * (*)(u8*, u8)) Area_RunSetupRecord)(script, op);
        } else {
            script = ((u8 * (*)(u8*, u8)) Area_RunSetupBranch)(script, op);
        }
        op = *script;
    }
}
