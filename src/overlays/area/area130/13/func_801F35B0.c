#include "area130_13.h"

MATCH void func_801F35B0(void) {
    g_MessageRequest = D_801F5058[g_MessageChoice];
    switch (g_MessageChoice) {
        case 0:
            g_SceneState.step_05  = 0xA;
            *g_ScriptVars         = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.state_04 = 6;
            break;
        case 1:
            *g_ScriptVars = 0;
            break;
    }
}
