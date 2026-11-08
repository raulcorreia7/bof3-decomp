#include "game_00.h"

MATCH void GFX_FreePaletteFadeTarget(void* target) {
    s32 index;

    index = 0;
    do {
        if (g_PaletteFades[index].target == target) {
            GFX_FreePaletteFade(index);
        }
        index += 1;
    } while (index < PALETTE_FADE_COUNT);
}
