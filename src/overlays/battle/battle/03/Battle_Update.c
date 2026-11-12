#include "battle_03.h"

/* func_801D1014 */
MATCH void Battle_Update(void) {
    s32 status = g_Battle.state;

    if (!(status & BATTLE_STATE_WINDOW_BUSY) && ((g_MenuPanelTasks[0].active == 0) || (g_Battle.phase.mode == BATTLE_MODE_RESULT)) &&
        ((g_Battle.outcome.event_flags & 0x2) == 0 || (g_Battle.phase.mode == BATTLE_MODE_RESULT))) {
        Battle_DispatchMode();
    }
    Battle_UpdateParty();
    Battle_UpdateEnemies();
    Battle_UpdateEvents();
    Area_UpdateCamera();
    Battle_UpdateEffects();
    Battle_UpdatePartyActors();
    Battle_UpdateEnemyActors();
    if (BATTLE_IS_SCRIPTED()) {
        func_801A0514();
    } else {
        func_801A061C();
    }
    Area_UpdateParty();
    Actor_DispatchAll();
    GFX_UpdatePaletteAnimations();
    func_8019625C();
    Menu_UpdatePanelTasks();
    Area_DrawScene();
}
