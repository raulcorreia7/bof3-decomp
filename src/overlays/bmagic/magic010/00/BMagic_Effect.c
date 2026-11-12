#include "magic010_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

#include "overlays/bmagic/Effect_StartPaletteFade.h"

/* Raises the red, green and blue offsets of the palette fade row the byte at +0x0B names by one per
 * frame and advances header.mode (byte 0x01) at sixteen. */
/* func_801EED0C */
MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[MAGIC010_TASK->timer].offset.red++;
    g_PaletteFades[MAGIC010_TASK->timer].offset.green++;
    g_PaletteFades[MAGIC010_TASK->timer].offset.blue++;
    if (++MAGIC010_TASK->unk_09 == 16) {
        MAGIC010_TASK->header.mode++;
    }
}

/* func_801EEE20 */
MATCH void Effect_FadePaletteOut(void) {
    g_PaletteFades[MAGIC010_TASK->timer].offset.red--;
    g_PaletteFades[MAGIC010_TASK->timer].offset.green--;
    g_PaletteFades[MAGIC010_TASK->timer].offset.blue--;
    if (--MAGIC010_TASK->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        MAGIC010_TASK->header.mode++;
    }
}

#include "shared/Effect_PlayOnce.h"
