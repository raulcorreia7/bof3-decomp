#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8070(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(15, 0x2C0000, 0x430000, AREA_ENTRY_MAP_LOADING);
            break;
        case 1:
            if (g_ScriptVars[0] == 8) {
                g_GameFlags |= 0x6;
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                SYS_SetFlag(g_SceneFlags, 4);
            }
            break;
        case 5:
            func_801BE1B0(1);
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                g_GameFlags ^= 0x80;
                Game_RequestAreaChange(26, 0x310000, 0x4B0000, AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                g_GameRequestKind = 1;
            }
            break;
        case 7:
            func_801BE1B0(2);
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                g_GameFlags ^= 0x80;
                Game_RequestAreaChange(26, 0x310000, 0x4B0000, AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                g_GameRequestKind = 1;
            }
            break;
    }
}
