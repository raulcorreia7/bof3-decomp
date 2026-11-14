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

    mode = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    GFX_AddPrim(6U, sizeof(DR_MODE));
    offset = (g_FrameBufferIndex + 2) * 8 + scene * 0x30;
    entry  = *(u32*)(D_80142CC0 + offset);
    if (entry != 0) {
        slot   = (u32*)&D_801459D0[g_AreaDrawMode];
        packet = (u32*)*slot;
        setaddr(packet, entry);
        *slot = *(u32*)(D_80142CC4 + offset);
    }
}
