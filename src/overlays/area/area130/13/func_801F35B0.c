#include "area130_13.h"

MATCH void func_801F35B0(void) {
    g_MessageRequest = D_801F5058[D_801490C7];
    switch (D_801490C7) {
        case 0:
            g_SceneState.step_05  = 0xA;
            *g_ScriptVars         = 0;
            D_80146865            = 0;
            D_80146866            = 0;
            D_80146867            = 0;
            g_SceneState.state_04 = 6;
            break;
        case 1:
            *g_ScriptVars = 0;
            break;
    }
}
