#include "game_00.h"

/* func_801C1630 */
MATCH void Party_LoadPalettes(void) {
    Actor* work;
    s32    i;
    u8*    block;

    for (i = 0; i < g_PartySize; i++) {
        work   = (Actor*)((u8*)g_Game.members + i * BATTLE_PARTY_STRIDE);
        block  = GAME_PALETTE_STAGE + i * 0x40;
        g_Task = work;
        GFX_FreePaletteFadeTarget(work);
        GFX_LoadPalette(block, 0);
    }
}
