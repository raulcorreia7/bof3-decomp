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

    if (GetGraphType() == 1) {
        mode = 0x225;
    } else if (GetGraphType() == 2) {
        mode = 0x225;
    } else {
        mode = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    GFX_AddPrim(6U, 0xCU);
    offset = (g_FrameBufferIndex + 2) * 8 + scene * 0x30;
    entry  = *(u32*)(D_80142CC0 + offset);
    if (entry != 0) {
        slot    = (u32*)&D_801459D0[g_AreaDrawMode];
        packet  = (u32*)*slot;
        *packet = (*packet & 0xFF000000) | (entry & 0xFFFFFF);
        *slot   = *(u32*)(D_80142CC4 + offset);
    }
}
