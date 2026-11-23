#include "engine/slus/slus.h"

/* Initializes the game runtime, then runs the permanent frame loop,
 * including the guarded EMI service/reset path.
 */
MATCH void SYS_Main(void) {
    GfxFrame* work;

    __main();
    g_SysHardwareInitialized = 0;
    SYS_InitRuntime();
    SYS_StartLogo();
    DrawSyncCallback(SYS_CaptureDrawTime);
    SYS_ThreadRegister(0, SYS_StartFrontend);

    for (;;) {
        VSync(2);
        rand();
        PutDispEnv(&g_GfxCurrentBuffer->disp);
        PutDrawEnv(&g_GfxCurrentBuffer->draw);
        GFX_PaletteUpload();
        GFX_UpdateTransferQueue();
        DrawOTag(g_GfxCurrentBuffer->ot + 7);
        SYS_UpdateKeyState();
        SND_VoiceUpdateStatus();

        g_GfxBufferIndex ^= 1;
        work               = &g_GfxBuffers[g_GfxBufferIndex];
        g_GfxCurrentBuffer = work;
        ClearOTagR(work->ot, 8);
        SYS_PrepareFrame();

        if ((g_PadStates[0].held & (PADselect | PADstart)) == (PADselect | PADstart)) {
            if (g_SysResetHoldFrames == 60) {
                if (EMI_IsReady() != 0) {
                    g_SysResetHoldFrames = 0;
                    SND_Exit();
                    SYS_ThreadStopAll();
                    SYS_ThreadRegister(0, SYS_StartFrontend);
                }
            } else {
                g_SysResetHoldFrames++;
            }
        } else {
            g_SysResetHoldFrames = 0;
        }

        SYS_ThreadRun();
        EMI_Update();
        g_SysLastVSync = VSync(1);
        DrawSync(0);
        SYS_LinkOt();
        g_FrameCount++;
    }
}
