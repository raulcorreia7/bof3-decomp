#include "shop_00.h"

/* File-local declarations: shared fill-style byte, shop panel/selection bytes,
 * the panel flag byte, the pad state halfwords and helpers owned by this
 * target or the executable overlay. */

MATCH void func_801D4E74(void) {
    s32 buttons;
    u8  prev;
    u8  index;

    MENU_DRAW_HEADER();
    WinDrawCueText(MENU_PROMPT_X, MENU_PROMPT_Y, 0x9D);
    SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 1);
    buttons = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    prev    = g_SaveSlotFirst;
    if ((buttons & PADLup) != 0) {
        index           = prev - 1;
        g_SaveSlotFirst = index;
        if ((s8)index < 0) {
            g_SaveSlotFirst = g_SaveSlotCount + (D_801E60FC != 0 && g_SaveSlotCount != 3) - 1;
        }
    } else if ((buttons & PADLdown) != 0) {
        index           = prev + 1;
        g_SaveSlotFirst = index;
        if (index > g_SaveSlotCount + (D_801E60FC != 0 && g_SaveSlotCount != 3) - 1) {
            g_SaveSlotFirst = 0;
        }
    }
    if (prev != g_SaveSlotFirst) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if ((g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        if (g_SaveSlots[g_SaveSlotFirst].source_index == GAME_NONE) {
            if (D_801E60FC != 0) {
                D_8014865B = 0;
                D_80148652 = 0xD;
            } else {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                D_80148652       = 0xC;
                g_SaveCardStatus = CARD_EVENT_CAPACITY;
            }
        } else {
            D_8014865B = 0;
            D_80148652 = D_80148652 + 1;
        }
    } else if ((g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_80148652 = 0xB;
    }
}
