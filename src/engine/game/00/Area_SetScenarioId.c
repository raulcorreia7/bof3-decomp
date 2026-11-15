#include "game_00.h"

/* func_801A3F3C */
MATCH void Area_SetScenarioId(u8* script) {
    u16 op;

    D_8014820C = (s8)g_SceneState.scenario_id;
    op         = *script;
    while ((u8)op != GAME_NONE) {
        if (op < 0xF0U) {
            script = ((u8 * (*)(u8*, u8)) func_801A4BF8)(script, op);
        } else {
            script = ((u8 * (*)(u8*, u8)) func_801A4400)(script, op);
        }
        op = *script;
    }
}
