#include "area048_13.h"

MATCH void func_801F4790(void) {
    MESSAGE_REQUEST_CLEAR();
    if (!(g_UIMessageChoice & 0x1)) {
        g_ScriptVars[0] = 0xB;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x05));
    } else {
        g_ScriptVars[0] = 1;
        Game_ClearScriptActive();
        g_ScenarioState.state_04 = 0;
        g_ScenarioState.step     = 0;
    }
}
