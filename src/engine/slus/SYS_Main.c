#include "engine/slus/slus.h"

/* Initializes the game runtime, then runs the permanent frame loop,
 * including the guarded EMI service/reset path.
 */
MATCH void SYS_Main(void) {
    u8* work;

    __main();
    g_SysHardwareInitialized = 0;
    SYS_InitRuntime();
    SYS_RunLogo();
    DrawSyncCallback(SYS_CaptureDrawTime);
    CallbackRegister(0, SYS_StartFrontend);

    for (;;) {
        VSync(2);
        rand();
        PutDispEnv((DISPENV*)g_GfxCurrentDisplayFrame);
        PutDrawEnv((DRAWENV*)(g_GfxCurrentDisplayFrame + 0x14));
        GFX_UploadPalette();
        GFX_RunTransferQueue();
        DrawOTag((u_long*)(g_GfxCurrentDisplayFrame + 0x8C));
        SYS_UpdateKeyState();
        SND_UpdateVoiceStatus();

        g_FrameBufferIndex ^= 1;
        work                     = g_GfxDisplayFrames + g_FrameBufferIndex * 0x90;
        g_GfxCurrentDisplayFrame = work;
        ClearOTagR((u_long*)(work + 0x70), 8);
        SYS_PrepareFrame();

        if ((g_InputHeld & (PADselect | PADstart)) == 0x900) {
            if (g_SysResetHoldFrames == 60) {
                if (EMI_LoaderIsReady() != 0) {
                    g_SysResetHoldFrames = 0;
                    SND_Exit();
                    CallbackStopAll();
                    CallbackRegister(0, SYS_StartFrontend);
                }
            } else {
                g_SysResetHoldFrames++;
            }
        } else {
            g_SysResetHoldFrames = 0;
        }

        CallbackRun();
        EMI_LoaderService();
        g_SysLastVSync = VSync(1);
        DrawSync(0);
        SYS_SubmitFrame();
        g_FrameCount++;
    }
}
