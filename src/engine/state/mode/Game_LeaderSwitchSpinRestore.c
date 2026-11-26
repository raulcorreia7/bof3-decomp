#include "engine/game/00/game_00.h"

/* func_801B26E0 */
/* Step 3: turns the leader one facing per frame while the timer falls and restores the mode 3 members; advances when unk_09 is 0. */
MATCH void Game_LeaderSwitchSpinRestore(void) {
    u8 i;
    u8 level;

    SELF(Actor)->timer -= 1;
    SELF(Actor)->direction = (SELF(Actor)->direction + 1) & 0x7;
    Script_Select(SELF(Actor)->direction);
    i     = 1;
    level = SELF(Actor)->timer;
    if (i < g_PartySize) {
        do {
            SELF_SET(&g_Game.members[i]);
            if (SELF(Actor)->header.mode == 3) {
                SELF(Actor)->tint.bytes.rgb.r = -(level << 5);
                SELF(Actor)->tint.bytes.rgb.g = SELF(Actor)->tint.bytes.rgb.r;
                SELF(Actor)->tint.bytes.rgb.b = SELF(Actor)->tint.bytes.rgb.r;
            }
            i++;
        } while (i < g_PartySize);
    }
    g_GameState = g_Game.members;
    SELF_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 0) {
        for (i = 1; i < g_PartySize; i++) {
            SELF_SET(&g_Game.members[i]);
            if (SELF(Actor)->header.mode == 3) {
                GFX_PaletteLoad(GAME_PALETTE_STAGE + (SELF(Actor)->unk_05 << 6), 0);
                SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                ACTOR_CLEAR_TINT();
                SELF(Actor)->tint.bytes.flags = 0;
                SELF(Actor)->timer            = 0;
                Actor_ClearVelocity();
                SELF(Actor)->unk_18  = 0;
                SELF(Actor)->unk_1C  = 0;
                SELF(Actor)->gravity = 0;
            }
        }
        SELF_SET(g_Game.members);
        g_Game.members[0].header.step += 1;
    }
}
