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
    jitter                        = (g_FrameCount & 0xF) << 20;
    TASK(Actor)->tint.bytes.rgb.r = 0;
    height                        = TASK(Actor)->pos.z.fixed - jitter;
    while (TASK(Actor)->vz < height) {
        func_801F3308(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, height, 1);
        TASK(Actor)->tint.bytes.rgb.r += 0x2A;
        if (TASK(Actor)->tint.bytes.rgb.r > 0x80) {
            TASK(Actor)->tint.steps.delta.r = -0x80;
        }
        height -= TO_COORD(256);
    }
    TASK(Actor)->tint.steps.delta.r = -1;
    func_801F3308(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, TASK(Actor)->vz, 0);
    if (g_ScriptVars[3] == 0xE) {
        TASK(Actor)->header.mode = 1;
    }
}
