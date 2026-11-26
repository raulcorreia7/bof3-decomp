#include "engine/game/00/game_00.h"

/* func_801B26E0 */
/* Step 3: turns the leader one facing per frame while the timer falls and restores the mode 3 members; advances when unk_09 is 0. */
MATCH void Game_LeaderSwitchSpinRestore(void) {
    u8 i;
    u8 level;

    TASK(Actor)->timer -= 1;
    TASK(Actor)->direction = (TASK(Actor)->direction + 1) & 0x7;
    Script_Select(TASK(Actor)->direction);
    i     = 1;
    level = TASK(Actor)->timer;
    if (i < g_PartySize) {
        do {
            TASK_SET(&g_Game.members[i]);
            if (TASK(Actor)->header.mode == 3) {
                TASK(Actor)->tint.bytes.rgb.r = -(level << 5);
                TASK(Actor)->tint.bytes.rgb.g = TASK(Actor)->tint.bytes.rgb.r;
                TASK(Actor)->tint.bytes.rgb.b = TASK(Actor)->tint.bytes.rgb.r;
            }
            i++;
        } while (i < g_PartySize);
    }
    g_GameState = g_Game.members;
    TASK_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 0) {
        for (i = 1; i < g_PartySize; i++) {
            TASK_SET(&g_Game.members[i]);
            if (TASK(Actor)->header.mode == 3) {
                GFX_PaletteLoad(GAME_PALETTE_STAGE + (TASK(Actor)->unk_05 << 6), 0);
                TASK(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                ACTOR_CLEAR_TINT();
                TASK(Actor)->tint.bytes.flags = 0;
                TASK(Actor)->timer            = 0;
                Actor_ClearVelocity();
                TASK(Actor)->unk_18  = 0;
                TASK(Actor)->unk_1C  = 0;
                TASK(Actor)->gravity = 0;
            }
        }
        TASK_SET(g_Game.members);
        g_Game.members[0].header.step += 1;
    }
}
