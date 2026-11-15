#include "batl_ovr_00.h"

/* func_801EF0A8 */
MATCH void Battle_UpdateGameOver(void) {
    func_801EF318();
    func_801EF180(0x80);
    func_801EF3B4(0x80);

    if (WINDOW_EFFECT_IDLE()) {
        u8* row = (u8*)g_Game.members;

        GFX_FreePaletteFadeTarget(row);
        GFX_FreePaletteFadeTarget(row + BATTLE_PARTY_STRIDE);
        GFX_FreePaletteFadeTarget(row + 0x280);
        Menu_ResetPanelTasks();
        g_Battle.outcome.event_flags = 0;
        g_Battle.outcome.options     = 0;
        g_Battle.encounter           = 0;
        g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
        g_Battle.phase.step          = 0;
        g_Battle.phase.sub_step      = 0;
        g_Battle.ui_step             = 0;
        g_Battle.ui_state            = 0;
        func_800ACF80();
        func_801E5A38();
        SND_Exit();
        SYS_ThreadReplace(SYS_StartFrontend);
    }
}
