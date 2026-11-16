#include "area188_13.h"

/* Applies the message menu's choice: no request is pending, the two row ids the
 * choice selects go to the script work record, and choice 1 of the first scenes
 * starts the script step. */
MATCH void func_801F477C(void) {
    Actor* work;

    work             = g_ScriptWorkRecord;
    g_MessageRequest = 0xFFFF;
    work->unk_18     = D_801F688C[g_MessageChoice * 2];
    FAKE_BARRIER(); /* FAKE: retail reads the choice again for the second row. */
    work->unk_1C = D_801F688D[g_MessageChoice * 2];
    FAKE_BARRIER(); /* FAKE: retail reads the choice again for the comparison. */

    if (g_SceneState.scenario_id < 0xD && g_MessageChoice == 1) {
        D_8014865F = 0;
        Game_SetScriptActive();
        g_SceneState.step_05  = 0x14;
        g_SceneState.state_04 = 0x8;
    }
}
