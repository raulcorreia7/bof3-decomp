#include "game_00.h"

/* func_801A3818 */
MATCH void Game_StartFadeBlack(void) {
    g_CurrentActor->unk_93 = GFX_AllocPaletteFade((u8*)g_Task, 0, 0, 0, 1);
    g_Task->unk_04         = 1;
}
