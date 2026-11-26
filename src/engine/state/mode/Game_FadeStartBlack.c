#include "engine/game/00/game_00.h"

/* func_801A3818 */
MATCH void Game_FadeStartBlack(void) {
    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(SELF(u8), 0, 0, 0, 1);
    SELF(Actor)->unk_04    = 1;
}
