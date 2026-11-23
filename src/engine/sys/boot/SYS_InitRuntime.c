#include "engine/slus/slus.h"

/* Initializes the runtime work buffers and subsystem state used by
 * the executable's boot loop.
 */
MATCH void SYS_InitRuntime(void) {
    GfxFrame* work;

    SYS_InitHardware();
    SYS_InitDisplay();
    work = g_GfxBuffers;
    SYS_ResetDisplayFrame(work);
    SYS_ResetDisplayFrame(work + 1);
    SYS_ThreadInit();
    g_GfxBufferIndex   = 0;
    g_GfxCurrentBuffer = work;
    GFX_ClearRect(0, 0, GFX_VRAM_WIDTH, GFX_VRAM_HEIGHT);
    DrawSync(0);
    SetDispMask(1);
    SYS_PrepareFrame();
}
