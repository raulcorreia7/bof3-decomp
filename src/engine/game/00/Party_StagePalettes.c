#include "game_00.h"

/* func_801C1630 */
MATCH void Party_StagePalettes(void) {
    Actor* work;
    s32    i;
    s32    block;

    for (i = 0; i < g_PartySize; i++) {
        work   = (Actor*)((u8*)g_BattlePartyBattlers + i * BATTLE_PARTY_STRIDE);
        block  = GAME_PALETTE_STAGE + i * 0x40;
        g_Task = work;
        GFX_FreePaletteFadeTarget(work);
        GFX_StagePalette(block, 0);
    }
}
