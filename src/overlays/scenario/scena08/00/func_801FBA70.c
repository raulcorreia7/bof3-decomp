#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBA70(void) {
    u8            index;
    SpawnedActor* actor;

    switch (g_ScenarioState.step_05) {
        case 0:
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WORKER, TO_COORD(78), TO_COORD(52), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            g_GamePrevSelection     = GAME_NONE;
            g_ScenarioState.step_05 = 100;
            break;
        case 100:
            if (g_GameAreaId == AREA_ID_DAUNA_MINE_WORKER) {
                index = Actor_FindFreeSpawned();
                if (index != GAME_NONE) {
                    actor               = &g_SpawnedActors[index];
                    actor->header.flags = ACTOR_FLAG_IN_USE;
                    actor->type         = 0x57;
                }
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0x1) {
                Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD_HALF(61), TO_COORD_HALF(13), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                g_GameRequestKind       = 0xFF;
                g_GamePrevSelection     = GAME_NONE;
                g_ScenarioState.step_05 = 2;
            }
            /* fallthrough */
        case 2:
            if (g_ScriptVars[0] == 0x2) {
                Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD_HALF(19), TO_COORD(24), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x6) {
                g_AreaSceneMode         = 1;
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x8) {
                Char_RebuildPartyStats();
                SYS_SetFlag(g_SceneFlags, 7);
                Game_RequestAreaChange(AREA_ID_DAUNA_WORLD_MAP, TO_COORD(27), TO_COORD(33), FACING_RIGHT);
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
    }
}
