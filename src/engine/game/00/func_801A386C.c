#include "game_00.h"

MATCH void func_801A386C(void) {
    u8 index;

    if (g_PaletteFades[g_CurrentActor->unk_93].offset.r < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.r = g_PaletteFades[g_CurrentActor->unk_93].offset.r + 1;
    }
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.g < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.g = g_PaletteFades[g_CurrentActor->unk_93].offset.g + 1;
    }
    if (g_PaletteFades[g_CurrentActor->unk_93].offset.b < COLOR_CHANNEL_MAX) {
        g_PaletteFades[g_CurrentActor->unk_93].offset.b = g_PaletteFades[g_CurrentActor->unk_93].offset.b + 1;
    }
    index = g_CurrentActor->unk_93;
    if ((g_PaletteFades[index].offset.b + g_PaletteFades[index].offset.g + g_PaletteFades[index].offset.r) == 3 * COLOR_CHANNEL_MAX) {
        GFX_PaletteFreeFade(index);
        GAME_WORK_AREA_PTR->interaction_flags = GAME_WORK_AREA_PTR->interaction_flags & ~ACTOR_INTERACTION_FADE_BLACK;
        SELF(Actor)->header.mode              = SELF(Actor)->unk_03;
        SELF(Actor)->unk_04                   = 0;
    }
}
