#include "batl_ovr_00.h"

/* func_801EF0A8 */
MATCH void Battle_RunGameOver(void) {
    func_801EF318();
    func_801EF180(0x80);
    func_801EF3B4(0x80);

    if (WINDOW_EFFECT_IDLE()) {
        u8* row = (u8*)g_BattlePartyBattlers;

        GFX_FreePaletteFadeTarget(row);
        GFX_FreePaletteFadeTarget(row + BATTLE_PARTY_STRIDE);
        GFX_FreePaletteFadeTarget(row + 0x280);
        Menu_ResetPanelTasks();
        g_BattleOutcome.event_flags = 0;
        g_BattleOutcome.options     = 0;
        g_BattleEncounter           = 0;
        g_BattleMode                = 0;
        g_BattleStep                = 0;
        g_BattleSubStep             = 0;
        g_BattleUIStep              = 0;
        g_BattleUIState             = 0;
        func_800ACF80();
        func_801E5A38();
        SND_Exit();
        CallbackReplace(SYS_StartFrontend);
    }
}
