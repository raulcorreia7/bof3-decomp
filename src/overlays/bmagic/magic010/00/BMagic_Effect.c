#include "magic010_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC14.h"

#include "overlays/bmagic/shared/Effect_StartPaletteFade.h"

/* Raises the red, green and blue offsets of the palette fade row the byte at +0x0B names by one per
 * frame and advances header.mode (byte 0x01) at sixteen. */
/* func_801EED0C */
MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[SELF(Magic010Task)->timer].offset.r++;
    g_PaletteFades[SELF(Magic010Task)->timer].offset.g++;
    g_PaletteFades[SELF(Magic010Task)->timer].offset.b++;
    if (++SELF(Magic010Task)->unk_09 == 16) {
        SELF(Magic010Task)->header.mode++;
    }
}

/* func_801EEE20 */
MATCH void Effect_FadePaletteOut(void) {
    g_PaletteFades[SELF(Magic010Task)->timer].offset.r--;
    g_PaletteFades[SELF(Magic010Task)->timer].offset.g--;
    g_PaletteFades[SELF(Magic010Task)->timer].offset.b--;
    if (--SELF(Magic010Task)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        SELF(Magic010Task)->header.mode++;
    }
}

#include "shared/Effect_PlayOnce.h"
