#include "start_08.h"

extern void        Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style); /* local: void read; a sibling copy is s32 */
extern volatile u8 g_SndMono;                                                                /* local: volatile access; a sibling copy is plain */

MATCH void func_801E18D0(void) {
    s32 pressed;

    D_80148654 = 0;
    Menu_DrawClutStrip(D_80144953);
    Menu_DrawHeaderBar(MENU_HEADER_X, 16, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    WinDrawCueText(28, 19, (u16)((s8)D_80148655 + 0xBC));
    func_801E26A8(0x1C, 0x40);
    func_801E2668(0xFF, 0x70, 0x26);
    Menu_DrawCursorSprite((((s8)D_80148655 * 0x30) + 0x76) & 0xFFFE, 42, 0);
    pressed = PAD_GetRepeatedButtons(g_InputPressed & INPUT_DIRECTIONAL);
    if (pressed & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        /* Retail reads this byte signed for the toggle test. */
        if (*(s8*)&D_80148655 == 0) {
            D_80148655 = 1;
        } else {
            D_80148655 = 0;
        }
    }
    if (pressed & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148655 = 7;
        D_80148652 += 1;
        return;
    }
    if (pressed & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148655 = 2;
        D_80148652 += 1;
        return;
    }
    if (g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        s8* mode = (s8*)&D_80148655;

        if (*mode == 0) {
            if (g_GameEntryState != 2) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
            }
            D_80148653 = 0;
            D_80148654 = 0;
            D_80148652 += 3;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        func_801E2668((u8)*mode, 0x70, 0x26);
        Menu_DrawCursorSprite(((*mode * 0x30) + 0x76) & 0xFFFE, 42, 0);
        D_80144950                      = 1;
        g_InputMasks[INPUT_SLOT_SPEAK]  = PADRdown | PADL2 | PADR2;
        g_InputMasks[INPUT_SLOT_MOVE]   = PADRright;
        g_InputMasks[INPUT_SLOT_ACTION] = PADRup;
        g_InputMasks[INPUT_SLOT_MENU]   = PADRleft;
        g_InputMasks[INPUT_SLOT_VIEW]   = PADR1;
        g_WindowStyle                   = 0;
        D_80144953                      = 0;
        g_SndMono                       = 0;
        D_80144954                      = 0;
        D_80144955                      = 0;
        g_AutoRun                       = 0;
        g_InputMasks[INPUT_SLOT_CHANGE] = PADL1;
        return;
    }
    if (g_GameEntryState == 2) {
        if (g_InputPressed & PADstart) {
            /* Both arms converge on the shared advance block. */
            goto advance;
        }
    } else if (g_InputPressed & g_InputMasks[INPUT_SLOT_CANCEL]) {
        goto advance; /* Shared advance block, as in retail. */
    }
    return;
advance:
    if (g_GameEntryState != 2) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    }
    D_80148654 = 0;
    D_80148653 = 0;
    D_80148652 += 3;
}
