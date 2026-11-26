#include "engine/game/00/game_00.h"

/* func_801A35D8 */
MATCH void Game_FadeStartWhite(void) {
    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(SELF(u8), 31, 31, 31, 1);
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(Actor)->unk_04 = 1;
}
