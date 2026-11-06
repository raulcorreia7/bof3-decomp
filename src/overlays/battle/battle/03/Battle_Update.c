#include "battle_03.h"

/* func_801D1014 */
MATCH void Battle_Update(void) {
    s32 status = g_BattleState;

    if (!(status & BATTLE_STATE_WINDOW_BUSY) && ((g_MenuPanelTasks[0].active == 0) || (g_BattleMode == 5)) &&
        ((g_BattleEventFlags & 2) == 0 || (g_BattleMode == 5))) {
        Battle_DispatchMode();
    }
    Battle_RunParty();
    Battle_RunEnemies();
    Battle_RunEvents();
    Area_StepCamera();
    Battle_RunEffects();
    Battle_UpdatePartyActors();
    Battle_UpdateEnemyActors();
    if (g_BattleEncounter != 0) {
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
