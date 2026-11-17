#include "game_00.h"

MATCH void func_801A3648(void) {
    u8 index;

    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.r != 0) {
        g_PaletteFades[index].offset.r -= 1;
    }
    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.g != 0) {
        g_PaletteFades[index].offset.g -= 1;
    }
    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.b != 0) {
        g_PaletteFades[index].offset.b -= 1;
    }
    index = g_CurrentActor->unk_93;
    if ((g_PaletteFades[index].offset.b + g_PaletteFades[index].offset.g + g_PaletteFades[index].offset.r) == 0) {
        GFX_FreePaletteFade(index);
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_FADE_WHITE;
        g_Task->header.mode = g_Task->unk_03;
        g_Task->unk_04      = 0;
    }
}
