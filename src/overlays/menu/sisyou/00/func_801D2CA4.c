#include "sisyou_00.h"

/* Main-RAM shop state, lookup tables, and working buffers. */

/* Overlay-local master stats: 6 signed stat-bonus bytes per master id. */

MATCH void func_801D2CA4(void) {
    s32 i;
    u8* edp;

    if (g_MasterBannerLock != 0) {
        Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_FAREWELL));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterStep     = 6;
        g_MasterSubStep  = 0;
    } else {
        i = 0;
        do {
            /* FAKE: shift form avoids the phantom stack slot * 0x140
             * allocates. */
            g_TextVariables[0][i] = g_Characters[g_Game.members[g_MasterMenuCursor].character_index].name[i];
            i += 1;
        } while (i < 5);
        D_801490DD                                                                 = 0;
        edp                                                                        = &g_SceneEventSelection;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].master_id = *edp;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].master_level =
            g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[0] =
            g_MasterStats[*edp].hp_bonus;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[1] =
            g_MasterStats[*edp].ap_bonus;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[2] =
            g_MasterStats[*edp].power_bonus;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[3] =
            g_MasterStats[*edp].defense_bonus;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[4] =
            g_MasterStats[*edp].agility_bonus;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[5] =
            g_MasterStats[*edp].intellect_bonus;
        Message_StartAreaMessage((s16)(g_MasterMessageIds[*edp] + MASTER_MESSAGE_ENROLLED));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterSubStep += 1;
    }
}
