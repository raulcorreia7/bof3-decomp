#include "game_00.h"

MATCH void GFX_FreePaletteFadeTarget(void* target) {
    s32 index;

    index = 0;
    do {
        if (D_80145BD4[index].target == target) {
            GFX_FreePaletteFade((u8)index);
        }
        index += 1;
    } while (index < GRAPHICS_PALETTE_FADE_COUNT);
}
