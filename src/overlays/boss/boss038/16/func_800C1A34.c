#include "boss038_16.h"

MATCH void func_800C1A34(void) {
    g_Battle.choose_ending_hook = func_800C1B10;
    g_Battle.end_hook           = func_800C1B74;
    g_Battle.boss_event_hook    = func_800C1B08;
    g_Battle.target_selector    = 0x40;
    TASK_SET(&g_BattleEnemyBattlers[7]);
    Battle_CenterCamera();
    g_AreaScrollTargetCoordX.fixed = g_AreaEncounterPlacement.origin.x.fixed + (TASK(PartyMember)->pos.x.fixed - g_AreaEncounterPlacement.origin.x.fixed) / 2;
    g_AreaScrollTargetCoordY.fixed = g_AreaEncounterPlacement.origin.y.fixed + (TASK(PartyMember)->pos.y.fixed - g_AreaEncounterPlacement.origin.y.fixed) / 2;
    g_AreaCameraSpeed              = 0x20;
}
