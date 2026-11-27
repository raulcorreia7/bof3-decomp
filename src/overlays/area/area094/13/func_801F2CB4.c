#include "area094_13.h"

MATCH void func_801F2CB4(void) {
    u8 value;

    g_UIMessageRequest = D_801F5358[g_UIMessageChoice];
    switch (g_UIMessageChoice) {
        case 0:
            break;

        case 1:
            if (!SYS_TestFlag(g_SceneFlags, 22)) {
                SYS_SetFlag(g_SceneFlags, 22);
                Game_SetScriptActive();
                SCRIPT_VARS_CLEAR_ALL();
                g_ScenarioState.step = 0;
                value                = 7;
                goto value_store;
            }
            if (!SYS_TestFlag(g_SceneFlags, 26)) {
                Game_SetScriptActive();
                value = 0x19;
            } else {
                Game_SetScriptActive();
                value = 0x32;
            }
            g_ScenarioState.step = value;
            value                = 7;
            SCRIPT_VARS_CLEAR_ALL();
        value_store:
            g_ScenarioState.state_04 = value;
            break;
    }
}
