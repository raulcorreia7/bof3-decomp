#include "engine/slus/slus.h"

/* Initializes the runtime work buffers and subsystem state used by
 * the executable's boot loop.
 */
MATCH void SYS_InitRuntime(void) {
    u8* work;

    SYS_InitHardware();
    SYS_InitDisplay();
    work = g_GfxDisplayFrames;
    SYS_ResetDisplayFrame(work);
    SYS_ResetDisplayFrame(work + 0x90);
    SYS_ThreadInit();
    g_FrameBufferIndex       = 0;
    g_GfxCurrentDisplayFrame = work;
    GFX_ClearRect(0, 0, 1024, 512);
    DrawSync(0);
    SetDispMask(1);
    SYS_PrepareFrame();
}
