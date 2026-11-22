#include "batl_ovr_00.h"

/* func_801EF0A8 */
MATCH void Battle_UpdateGameOver(void) {
    func_801EF318();
    func_801EF180(0x80);
    func_801EF3B4(0x80);

    if (WINDOW_EFFECT_IDLE()) {
        PartyMember* members = g_Game.members;

        GFX_PaletteFreeFadeTarget(&members[0]);
        GFX_PaletteFreeFadeTarget(&members[1]);
        GFX_PaletteFreeFadeTarget(&members[2]);
        UI_PanelResetTasks();
        g_Battle.outcome.event_flags = 0;
        g_Battle.outcome.options     = 0;
        g_Battle.encounter           = 0;
        g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
        g_Battle.phase.step          = 0;
        g_Battle.phase.sub_step      = 0;
        g_Battle.ui_step             = 0;
        g_Battle.ui_mode             = 0;
        func_800ACF80();
        func_801E5A38();
        SND_Exit();
        SYS_ThreadReplace(SYS_StartFrontend);
    }
}
