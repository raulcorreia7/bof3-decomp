#include "engine/slus/slus.h"
#include "common/copy.h"

/* displays the boot exception register dump and loops forever
 * updating the double-buffered debug screen.
 */
MATCH void SYS_ShowException(void) {
    u32*         exception_frame;
    Cpy16*       src;
    Cpy16*       dst;
    Cpy16*       end;
    u32          saved_context[48];
    u32          exception_code;
    u32*         exception_pc;
    unsigned int i;
    s16          y;
    u8           x_value;
    s16          x_label;

    exception_frame = **(u32***)0x108;
    src             = (Cpy16*)exception_frame;
    dst             = (Cpy16*)saved_context;
    end             = (Cpy16*)(exception_frame + 48);
    do {
        *dst++ = *src++;
    } while (src != end);

    exception_code = exception_frame[0x26];
    exception_pc   = (u32*)exception_frame[0x22];

    ExitCriticalSection();

    while (1) {
        VSync(2);
        x_label = 0x14;
        y       = 60;
        x_value = 0x3C;

        PutDispEnv(&g_GfxCurrentBuffer->disp);
        PutDrawEnv(&g_GfxCurrentBuffer->draw);
        DrawOTag(g_GfxCurrentBuffer->ot + 7);

        g_GfxBufferIndex   = g_GfxBufferIndex ^ 0x1;
        g_GfxCurrentBuffer = &g_GfxBuffers[g_GfxBufferIndex];

        ClearOTagR(g_GfxCurrentBuffer->ot, 8);
        SYS_PrepareFrame();

        for (i = 0; i < 18; i++) {
            UI_TextDrawGlyphString(x_label, y, 0, (void*)g_ExceptionNames[i]);
            TEXT_Format(g_UITextFormatBuffer, g_ExceptionHexFormat, saved_context[i + 2]);
            UI_TextDrawGlyphString(x_value, y, 0, (void*)g_UITextFormatBuffer);
            y += 8;
        }

        x_label = 0xA0;
        y       = 60;
        x_value = 0xC8;

        for (i = 18; i < 37; i++) {
            UI_TextDrawGlyphString(x_label, y, 0, (void*)g_ExceptionNames[i]);
            TEXT_Format(g_UITextFormatBuffer, g_ExceptionHexFormat, saved_context[i + 2]);
            UI_TextDrawGlyphString(x_value, y, 0, (void*)g_UITextFormatBuffer);
            y += 8;
        }

        UI_TextDrawGlyphString(20, 20, 0, (void*)g_ExceptionTitle);
        UI_TextDrawGlyphString(100, 20, UI_TEXT_HIGHLIGHT, *(void* const*)((u8*)g_ExceptionCauseNames + (exception_code & CAUSE_EXCMASK)));

        TEXT_Format(g_UITextFormatBuffer, g_ExceptionHexFormat, exception_pc);
        UI_TextDrawGlyphString(70, 36, 3, (void*)g_UITextFormatBuffer);
        TEXT_Format(g_UITextFormatBuffer, g_ExceptionHexFormat, exception_pc[0]);
        UI_TextDrawGlyphString(142, 36, 4, (void*)g_UITextFormatBuffer);

        DrawSync(0);
        SYS_LinkOt();
        g_FrameCount += 1;
    }
}
