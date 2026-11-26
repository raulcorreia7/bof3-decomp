#include "engine/game/00/game_00.h"

/* func_801C1630 */
MATCH void Party_LoadPalettes(void) {
    Actor* work;
    s32    i;
    u8*    block;

    for (i = 0; i < g_PartySize; i++) {
        work  = (Actor*)&g_Game.members[i];
        block = GAME_PALETTE_STAGE + i * 0x40;
        SELF_SET(work);
        GFX_PaletteFreeFadeTarget(work);
        GFX_PaletteLoad(block, 0);
    }
}
