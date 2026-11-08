#include "game_00.h"

MATCH void func_801A3648(void) {
    u8 index;

    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.red != 0) {
        g_PaletteFades[index].offset.red -= 1;
    }
    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.green != 0) {
        g_PaletteFades[index].offset.green -= 1;
    }
    index = g_CurrentActor->unk_93;
    if (g_PaletteFades[index].offset.blue != 0) {
        g_PaletteFades[index].offset.blue -= 1;
    }
    index = g_CurrentActor->unk_93;
    if ((g_PaletteFades[index].offset.blue + g_PaletteFades[index].offset.green + g_PaletteFades[index].offset.red) ==
        0) {
        GFX_FreePaletteFade(index);
        ((Actor*)g_CurrentActor)->interaction_flags &= ~ACTOR_FLAG_FADE_WHITE;
        g_Task->header.mode = g_Task->unk_03;
        g_Task->unk_04      = 0;
    }
}
