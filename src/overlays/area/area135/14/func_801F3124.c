#include "area135_14.h"

/* Draws the tint curtain at the task: a line cross every 256 units from the task z down to its
 * vz, the frame cycle offsetting them. The tint red steps 42 a line, wraps to -128 and ends at -1. */
MATCH void func_801F3124(void) {
    u16 tpage;
    s32 height;
    s32 jitter;

    tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x140, 0);
    GFX_AddDitheredDrawMode(3, tpage);
    func_801F32A0(0);
    jitter                     = (g_FrameCount & 0xF) << 20;
    g_Task->tint.bytes.rgb.red = 0;
    height                     = g_Task->pos.z.fixed - jitter;
    while (g_Task->vz < height) {
        func_801F3308(g_Task->pos.x.fixed, g_Task->pos.y.fixed, height, 1);
        g_Task->tint.bytes.rgb.red += 0x2A;
        if (g_Task->tint.bytes.rgb.red > 0x80) {
            g_Task->tint.signed_bytes.delta.red = -0x80;
        }
        height -= TO_COORD(256);
    }
    g_Task->tint.signed_bytes.delta.red = -1;
    func_801F3308(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->vz, 0);
    if (D_80146867 == 0xE) {
        g_Task->header.mode = 1;
    }
}
