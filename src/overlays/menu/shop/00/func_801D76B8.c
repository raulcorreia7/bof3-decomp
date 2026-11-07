#include "shop_00.h"

MATCH void func_801D76B8(void) {
    s32 input;
    u8* cursor;
    u8  id;

    func_801D8050(0);
    cursor = &D_8014865D;
    WinDrawCueText(28, 21, (u16)((s8)*cursor + 0x65));
    func_801D7E1C(D_80148656, 0x98, 0x3F, 0, 0xFF);
    Menu_DrawCursorFrame(0x11, ((s8)D_80148656 * 0x36 + 0x3E) & 0xFFFE, 0x80, 0x34, 0, 6);
    Menu_DrawCursorSprite(0x9B, (s8)*cursor * 0xD + 0x44, 0);
    input = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (input & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        (*cursor)++;
        if ((s8)*cursor >= 8) {
            *cursor = 0;
        }
    }
    if (input & PADLup) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        if (--(*(s8*)&D_8014865D) < 0) {
            *(s8*)&D_8014865D = 7;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        id = D_80145FCC[(s8)D_80148656][0];
        if (g_Zenny < (g_Characters[id].level * 10)) {
            SND_PlayCue(EMI_CUE_ID(1, 7));
            D_8014865B = 0xB;
            D_8014865F = 0xC;
            D_80148654 = 0x3C;
            D_80148651 += 5;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            D_8014865B = 0;
            D_80148651 += 1;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        (*(s8*)&D_80148651)--;
    }
}
