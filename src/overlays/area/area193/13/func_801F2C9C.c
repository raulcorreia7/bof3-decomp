#include "area193_13.h"

MATCH s32 func_801F2C9C(void) {
    g_MessageRequest = D_801F3A08[D_801490C7];
    if (D_801490C7 == 1) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 1;
        g_SceneState.step_05  = 0;
    }
}
