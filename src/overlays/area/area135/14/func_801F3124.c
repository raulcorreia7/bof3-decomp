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
    SELF(Actor)->tint.bytes.rgb.r = 0;
    height                        = SELF(Actor)->pos.z.fixed - jitter;
    while (SELF(Actor)->vz < height) {
        func_801F3308(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, height, 1);
        SELF(Actor)->tint.bytes.rgb.r += 0x2A;
        if (SELF(Actor)->tint.bytes.rgb.r > 0x80) {
            SELF(Actor)->tint.steps.delta.r = -0x80;
        }
        height -= TO_COORD(256);
    }
    SELF(Actor)->tint.steps.delta.r = -1;
    func_801F3308(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->vz, 0);
    if (g_ScriptVars[3] == 0xE) {
        SELF(Actor)->header.mode = 1;
    }
}
