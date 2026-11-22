#include "engine/game/00/game_00.h"

/* func_801A35D8 */
MATCH void Game_FadeStartWhite(void) {
    g_CurrentActor->unk_93 = GFX_PaletteAllocFade(TASK(u8), 31, 31, 31, 1);
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_04 = 1;
}
