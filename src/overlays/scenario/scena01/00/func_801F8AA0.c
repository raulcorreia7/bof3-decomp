#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8AA0(void) {
    SYS_DISPATCH_BYTE(D_801FE2A8, g_ScenarioState.state_04);
}

MATCH void func_801F8ADC(void) {
}

MATCH void func_801F8AE4(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[1]         = 1;
                g_ScriptVars[2]         = 1;
                g_ScenarioState.step_05 = 1;
                func_8019FA28(0x9, 0x470000, 0x1D0000, 3);
            }
            break;
        case 1:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Area_ScrollStartRoute(0);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1E) {
                SYS_SetFlag(g_SceneFlags, 0);
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                SCENARIO_RETURN_TO_START();
                func_8019FA28(0xA, 0x2B0000, 0x200000, 3);
            }
            break;
    }
}
