#include "game_00.h"

MATCH void func_801A386C(void) {
    u8 index;

    if (g_PaletteFades[g_CurrentActor->unk_93].offset.red < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.red = g_PaletteFades[g_CurrentActor->unk_93].offset.red + 1;
    }
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.green < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.green = g_PaletteFades[g_CurrentActor->unk_93].offset.green + 1;
    }
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.blue < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.blue = g_PaletteFades[g_CurrentActor->unk_93].offset.blue + 1;
    }
    index = g_CurrentActor->unk_93;
    if ((g_PaletteFades[index].offset.blue + g_PaletteFades[index].offset.green + g_PaletteFades[index].offset.red) == 3 * COLOR_CHANNEL_MAX) {
        GFX_FreePaletteFade(index);
        GAME_WORK_AREA_PTR->interaction_flags = GAME_WORK_AREA_PTR->interaction_flags & ~ACTOR_FLAG_FADE_BLACK;
        g_Task->header.mode                   = g_Task->unk_03;
        g_Task->unk_04                        = 0;
    }
}
