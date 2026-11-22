#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FC5B4(void) {
}

MATCH void func_801FC5BC(void) {
}

MATCH void func_801FC5C4(void) {
}

MATCH void func_801FC5CC(void) {
}

MATCH void func_801FC5D4(void) {
}

MATCH void func_801FC5DC(void) {
}

MATCH void func_801FC5E4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 1;
}

MATCH void func_801FC630(void) {
}

MATCH void func_801FC638(void) {
}

MATCH void func_801FC640(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0x14;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 4;
}

MATCH void func_801FC690(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0x14;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC6E0(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 2;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC738(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 8;
}

MATCH void func_801FC784(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0x1e;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 8;
}

MATCH void func_801FC7D4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0xA;
    g_ScenarioState.state_04 = 1;
}

MATCH s32 func_801FC80C(s32 y) {
    if ((g_GameAreaId == AREA_ID_STEEL_BEACH_MAP) && (SYS_TestFlag(g_SceneFlags, 0) != 0)) {
        if (y <= TO_COORD(22)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0x3C;
            g_ScenarioState.state_04 = 2;
            return 1;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
