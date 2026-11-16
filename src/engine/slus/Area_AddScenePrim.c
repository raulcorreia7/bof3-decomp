#include "engine/slus/slus.h"

/* chooses the draw mode for the current scene, appends a 12-byte
 * primitive, then re-links the scene's cached packet into the ordering-table
 * slot selected by g_AreaDrawMode when the scene entry is live.
 */
MATCH void Area_AddScenePrim(s32 scene) {
    u32* slot;
    u32* packet;
    u32  entry;
    s32  mode;
    s32  offset;

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(6U, mode);
    offset = (g_GfxBufferIndex + 2) * 8 + scene * 0x30;
    entry  = *(u32*)(D_80142CC0 + offset);
    if (entry != 0) {
        slot   = (u32*)&D_801459D0[g_AreaDrawMode];
        packet = (u32*)*slot;
        setaddr(packet, entry);
        *slot = *(u32*)(D_80142CC4 + offset);
    }
}
