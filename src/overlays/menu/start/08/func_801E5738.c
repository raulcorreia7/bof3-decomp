#include "start_08.h"

/* The staged shop row is a 0x1C-byte record and the byte at +0x15 marks the
 * row hidden (0xFF); g_SaveSlots[0].source_index is that byte of the first row, so the cursor's
 * row sits one stride per index above it. */
#define SHOP_ROW_STRIDE 0x1C

MATCH void func_801E5738(void) {
    s32 pressed;
    u8  prev_row;
    u8  row;

    Menu_DrawClutStrip(D_80144953);
    MENU_DRAW_HEADER();
    UI_DrawText(28, 21, 0, 255U, Message_GetText(0xAC));
    SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 1U);
    pressed  = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    prev_row = g_SaveSlotFirst;
    if (pressed & PADLup) {
        row             = prev_row - 1;
        g_SaveSlotFirst = row;
        if ((s8)row < 0) {
            g_SaveSlotFirst = g_SaveSlotCount - 1;
        }
    } else {
        if (pressed & PADLdown) {
            g_SaveSlotFirst = prev_row + 1;
            if ((g_SaveSlotFirst & BYTE_MASK) >= g_SaveSlotCount) {
                g_SaveSlotFirst = 0;
            }
        }
    }
    if (prev_row != g_SaveSlotFirst) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*(&g_SaveSlots[0].source_index + (g_SaveSlotFirst * SHOP_ROW_STRIDE)) != GAME_NONE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            D_8014865B = 1;
            g_MenuStartStep++;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_MenuStartStep = 0xC;
    }
}
