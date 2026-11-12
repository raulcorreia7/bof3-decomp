#include "engine/slus/slus.h"

/* unless bit 0 of g_SceneState.flags_01 is set, re-tints the palette working copy via func_8015822C (row seeds 0xFFFF
 * and 0xFFF, the cue in delta as the red/green/blue delta) and walks the palette record list
 * g_AreaMapBundle.list_base_22 through func_801580A4, which marks the palette dirty. */
MATCH void Area_UpdatePaletteTint(s32 delta) {
    if ((g_SceneState.flags_01 & 0x1) == 0) {
        Area_ApplyPaletteTint(0xFFFF, 0xFFF, delta, delta, delta);
        Area_CyclePalette();
    }
}
