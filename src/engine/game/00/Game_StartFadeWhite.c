#include "game_00.h"

/* func_801A35D8 */
MATCH void Game_StartFadeWhite(void) {
    g_CurrentActor->unk_93 = GFX_AllocPaletteFade((u8*)g_Task, 31, 31, 31, 1);
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_04 = 1;
}
