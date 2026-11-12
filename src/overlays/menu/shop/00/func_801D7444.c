#include "shop_00.h"

MATCH void func_801D7444(void) {
    u8* cursor;
    u8  count;
    u8  index;
    s32 input;

    count = Party_CountOrder(PARTY_ORDER_FIELD);
    func_801D8050(0);
    WinDrawCueText(28, 21, 0x63);
    cursor = &D_80148656;
    func_801D7E1C(*cursor, 152, 63, 0, 0xFF);
    Menu_DrawCursorFrame(17, ((s8)*cursor * 0x36 + 0x3E) & 0xFFFE, 128, 52, 1, 6);

    input = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (input & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        index   = *cursor + 1;
        *cursor = index;
        if ((s8)index >= (s8)count) {
            *cursor = 0;
        }
    }
    if (input & PADLup) {
        u8* prev;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        prev  = &D_80148656;
        index = *prev - 1;
        *prev = index;
        if ((s8)index < 0) {
            *prev = count - 1;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_Characters[g_Game.members[(s8)D_80148656].character_index].inoculations != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            D_8014865B = 1;
            D_8014865F = 2;
            D_80148654 = 0x3C;
            D_80148651 += 6;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            D_8014865D = 0;
            D_80148651 += 1;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_8014865B = 0xF;
        D_80148651 = 6;
        D_80148654 = 0x3C;
    }
}
