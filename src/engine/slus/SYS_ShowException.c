#include "engine/slus/slus.h"

typedef struct {
    u32 word[4];
} ExceptionQuad;

/* displays the boot exception register dump and loops forever
 * updating the double-buffered debug screen.
 */
MATCH void SYS_ShowException(void) {
    const u32*     exception_frame;
    ExceptionQuad* src;
    ExceptionQuad* dst;
    ExceptionQuad* end;
    u32            saved_context[48];
    u32            exception_code;
    const u32*     exception_pc;
    unsigned int   i;
    s16            y;
    u8             x_value;
    s16            x_label;

    exception_frame = **(const u32***)0x108;
    src             = (ExceptionQuad*)exception_frame;
    dst             = (ExceptionQuad*)saved_context;
    end             = (ExceptionQuad*)(exception_frame + 48);
    do {
        *dst++ = *src++;
    } while (src != end);

    exception_code = exception_frame[0x26];
    /* FAKE: pins the code spill before the PC load. */
    FAKE_BARRIER();
    exception_pc = (const u32*)exception_frame[0x22];

    ExitCriticalSection();

    while (1) {
        VSync(2);
        x_label = 0x14;
        y       = 60;
        x_value = 0x3C;

        PutDispEnv((DISPENV*)g_GfxCurrentDisplayFrame);
        PutDrawEnv((DRAWENV*)(g_GfxCurrentDisplayFrame + 0x14));
        DrawOTag((u_long*)(g_GfxCurrentDisplayFrame + 0x8C));

        g_FrameBufferIndex       = g_FrameBufferIndex ^ 0x1;
        g_GfxCurrentDisplayFrame = &g_GfxDisplayFrames[g_FrameBufferIndex * 0x90];

        ClearOTagR((u_long*)(g_GfxCurrentDisplayFrame + 0x70), 8);
        SYS_PrepareFrame();

        for (i = 0; i < 18; i++) {
            UI_DrawGlyphString(x_label, y, 0, (void*)D_8017F470[i]);
            TEXT_Format(g_UiFormatBuffer, D_80149990, saved_context[i + 2]);
            UI_DrawGlyphString(x_value, y, 0, (void*)g_UiFormatBuffer);
            y += 8;
        }

        x_label = 0xA0;
        y       = 60;
        x_value = 0xC8;

        for (i = 18; i < 37; i++) {
            UI_DrawGlyphString(x_label, y, 0, (void*)D_8017F470[i]);
            TEXT_Format(g_UiFormatBuffer, D_80149990, saved_context[i + 2]);
            UI_DrawGlyphString(x_value, y, 0, (void*)g_UiFormatBuffer);
            y += 8;
        }

        UI_DrawGlyphString(20, 20, 0, (void*)PTR_s_EXCEPTION_8017f504);
        UI_DrawGlyphString(100, 20, 2, *(void* const*)((const u8*)PTR_s_INTERRRUPT_8017f508 + (exception_code & 0x3C)));

        TEXT_Format(g_UiFormatBuffer, D_80149990, exception_pc);
        UI_DrawGlyphString(70, 36, 3, (void*)g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, D_80149990, exception_pc[0]);
        UI_DrawGlyphString(142, 36, 4, (void*)g_UiFormatBuffer);

        DrawSync(0);
        SYS_SubmitFrame();
        g_FrameCount += 1;
    }
}
