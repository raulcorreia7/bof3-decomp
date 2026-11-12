#include "batl_ovr_00.h"

/* Puts the three party members on the game-over screen: gives each its script, its
 * start position from the table, and marks it drawn, then fades in and advances. */
MATCH void func_801EEC7C(void) {
    u8* count;
    u8* step;

    if (!WINDOW_EFFECT_IDLE()) {
        return;
    }
    count                      = &g_BattlePartyCount;
    g_MenuPanelTasks[0].active = 0;
    if (*count != 0) {
        TASK_SET(&g_Game.members[0]);
        Actor_RequestScript(g_Game.members[0].facing + 0x1C);
        g_Game.members[0].unk_24 |= 0x80;
        g_Game.members[0].unk_2E.half = D_801EF60C[*count - 1][0][0];
        g_Game.members[0].unk_30.half = D_801EF60C[*count - 1][0][1];
        g_Game.members[0].unk_29      = 1;
        GFX_FreePaletteFadeTarget(&g_Game.members[0]);
        if (*count >= 2) {
            TASK_SET(&g_Game.members[1]);
            Actor_RequestScript(g_Game.members[1].facing + 0x1C);
            g_Game.members[1].unk_24 |= 0x80;
            g_Game.members[1].unk_2E.half = D_801EF60C[*count - 1][1][0];
            g_Game.members[1].unk_30.half = D_801EF60C[*count - 1][1][1];
            g_Game.members[1].unk_29      = 1;
            GFX_FreePaletteFadeTarget(&g_Game.members[1]);
            if (*count == 3) {
                TASK_SET(&g_Game.members[2]);
                Actor_RequestScript(g_Game.members[2].facing + 0x1C);
                g_Game.members[2].unk_24 |= 0x80;
                g_Game.members[2].unk_2E.half = D_801EF60C[*count - 1][2][0];
                g_Game.members[2].unk_30.half = D_801EF60C[*count - 1][2][1];
                g_Game.members[2].unk_29      = 1;
                GFX_FreePaletteFadeTarget(&g_Game.members[2]);
            }
        }
    }
    func_800ACF80();
    func_801E5A38();
    UI_SetMode(UI_MODE_LONG_FADE_IN);
    step = &g_BattleUIStep;
    *step += 1;
}
