#include "area133_13.h"

MATCH void func_801F2C1C(void) {
    Actor* work;

    work             = g_ScriptWorkRecord;
    g_MessageRequest = MESSAGE_NONE;
    work->unk_18     = D_801F3DF0[g_MessageChoice].unk_0;
    FAKE_BARRIER(); /* FAKE: re-reads the choice for the second byte. */
    work->unk_1C = D_801F3DF0[g_MessageChoice].unk_1;
    FAKE_BARRIER(); /* FAKE: re-reads the choice for the dispatch. */
    switch (g_MessageChoice) {
        case 0:
        case 1:
            break;
        case 2:
            D_8014865F = 0;
            Game_SetScriptActive();
            g_SceneState.step_05  = 0x1E;
            g_AreaDrawFlags       = 0;
            g_SceneState.state_04 = 4;
            break;
        case 3:
        case 4:
        case 5:
            break;
    }
}
