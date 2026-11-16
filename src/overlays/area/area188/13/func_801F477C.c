#include "area188_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F477C(void) {
    Actor* work;

    work             = g_ScriptWorkRecord;
    g_MessageRequest = 0xFFFF;
    work->unk_18     = D_801F688C[g_MessageChoice * 2];
    work->unk_1C     = D_801F688D[g_MessageChoice * 2];

    if (g_SceneState.scenario_id < 0xD && g_MessageChoice == 1) {
        D_8014865F = 0;
        Game_SetScriptActive();
        g_SceneState.step_05  = 0x14;
        g_SceneState.state_04 = 0x8;
    }
}
#else
INCLUDE_ASM(func_801F477C);
#endif
