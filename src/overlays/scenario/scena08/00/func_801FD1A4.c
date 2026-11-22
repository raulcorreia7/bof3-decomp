#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD1A4(void) {
    SpawnedActor* record;
    u8*           progress;
    u8            progress_value;
    u16*          countdown;
    u16           countdown_value;
    u8            object_index;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            Area_StartScrollRoute(0);
            g_ScenarioState.step_05 = 1;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            break;
        case 1:
            progress       = &g_ScriptVars[0];
            progress_value = *progress;
            if ((progress_value & 0xFF) != 0x14) {
                break;
            }
            *progress                = progress_value + 1;
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step_05  = 2;
            break;
        case 2:
            countdown       = &g_ScenarioState.timer_06;
            countdown_value = *countdown - 1;
            *countdown      = countdown_value;
            if (countdown_value != 0) {
                break;
            }
            g_ScenarioState.step_05 = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            Game_RequestAreaChange(0xD, TO_COORD(25), TO_COORD(16), 0x84);
            SYS_SetFlag(g_SceneFlags, 0xF);
            goto reset;
        case 4:
            break;
        case 5:
            Scene_SetupParty(5);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            object_index                = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = object_index;
            if (object_index != 0xFF) {
                record               = &g_SpawnedActors[object_index];
                record->header.flags = 1;
                record->type         = 0x5F;
                record->header.mode  = 6;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step_05  = 7;
            break;
        case 7:
            countdown       = &g_ScenarioState.timer_06;
            countdown_value = *countdown - 1;
            *countdown      = countdown_value;
            if (countdown_value != 0) {
                break;
            }
            g_ScriptVars[0] = 0;
            Game_ClearScriptActive();
            SND_SEPlay(0x203);
            SYS_SetFlag(g_SceneFlags, 0x10);
            Game_RequestAreaChange(0xF, TO_COORD_HALF(25), TO_COORD(81), 1);
        reset:
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}
