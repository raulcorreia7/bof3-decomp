#include "sisyou_00.h"

/* Stock list (stride 0x140 per entry) and the character records' master id
 * byte at +0x1B (stride 0xA4). */

/* Front-end phase byte owned by the main executable. */

MATCH void func_801D3390(void) {
    s32 i;

    if (g_MasterBannerLock != 0) {
        Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_FAREWELL));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterStep     = 6;
        g_MasterSubStep  = 0;
    } else {
        for (i = 0; i < 5; i++) {
            /* FAKE: shift form avoids the phantom stack slot * 0x140
             * allocates. */
            g_TextVariables[0][i] = g_Characters[g_Game.members[g_MasterMenuCursor].character_index].name[i];
        }
        D_801490DD                                                                             = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].master_id             = 0xFF;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].master_level          = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[0] = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[1] = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[2] = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[3] = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[4] = 0;
        g_Characters[g_Game.members[g_MasterMenuCursor].character_index].level_up_modifiers[5] = 0;
        Message_StartAreaMessage((s16)(g_MasterMessageIds[g_SceneEventSelection] + MASTER_MESSAGE_DISMISSED));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterSubStep += 1;
    }
}
