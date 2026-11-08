#include "battle_03.h"

/* func_801D1014 */
MATCH void Battle_Update(void) {
    s32 status = g_Battle.state;

    if (!(status & BATTLE_STATE_WINDOW_BUSY) && ((g_MenuPanelTasks[0].active == 0) || (g_Battle.phase.mode == 5)) &&
        ((g_Battle.outcome.event_flags & 2) == 0 || (g_Battle.phase.mode == 5))) {
        Battle_UpdateMode();
    }
    Battle_UpdateParty();
    Battle_UpdateEnemies();
    Battle_UpdateEvents();
    Area_StepCamera();
    Battle_UpdateEffects();
    Battle_UpdatePartyActors();
    Battle_UpdateEnemyActors();
    if (g_Battle.encounter != 0) {
        func_801A0514();
    } else {
        func_801A061C();
    }
    Area_RunParty();
    Actor_DispatchAll();
    GFX_UpdatePaletteAnimations();
    func_8019625C();
    Menu_RunPanelTasks();
    Area_DrawScene();
}
