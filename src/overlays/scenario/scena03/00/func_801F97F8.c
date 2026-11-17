#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F97F8(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            Scene_SetupParty(1);
            g_ScriptVars[0]         = 0xA;
            g_ScenarioState.step_05 = 1;
            break;

        case 1:
            if (g_ScriptVars[0] == 0x28) {
                g_ScenarioState.state_04 = 1;
                g_ScenarioState.step_05  = 1;
            }
            break;
    }
}
