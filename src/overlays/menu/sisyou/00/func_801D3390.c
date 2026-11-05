#include "sisyou_00.h"

/* Stock list (stride 0x140 per entry) and the character records' master id
 * byte at +0x1B (stride 0xA4). */

/* Front-end phase byte owned by the main executable. */

MATCH void func_801D3390(void) {
    s32 i;

    if (g_MasterBannerLock != 0) {
        Message_StartAreaMessage((s16)(g_MasterMessageIds[D_801448ED] + 4));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterStep     = 6;
        g_MasterSubStep  = 0;
    } else {
        for (i = 0; i < 5; i++) {
            /* FAKE: shift form avoids the phantom stack slot * 0x140
             * allocates. */
            g_TextVariables[0][i] = g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].name[i];
        }
        D_801490DD                                                                          = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].master_id             = 0xFF;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].master_level          = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[0] = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[1] = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[2] = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[3] = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[4] = 0;
        g_Characters[D_80145FCC.bytes[(g_MasterMenuCursor * 5) << 6]].level_up_modifiers[5] = 0;
        Message_StartAreaMessage((s16)(g_MasterMessageIds[D_801448ED] + 0xC));
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        g_MasterSubStep += 1;
    }
}
