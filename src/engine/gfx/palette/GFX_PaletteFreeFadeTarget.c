#include "engine/game/00/game_00.h"

MATCH void GFX_PaletteFreeFadeTarget(void* owner) {
    s32 index;

    index = 0;
    do {
        if (g_PaletteFades[index].target == owner) {
            GFX_PaletteFreeFade(index);
        }
        index += 1;
    } while (index < PALETTE_FADE_COUNT);
}
