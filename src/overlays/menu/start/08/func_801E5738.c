#include "start_08.h"

/* The staged shop record is a 0x1C-byte slot and the byte at +0x15 marks the
 * slot hidden (0xFF); g_SaveSlots[0].bytes.card_index is that byte of the first slot, so the cursor's
 * slot sits one stride per index above it. */
#define SHOP_SLOT_STRIDE 0x1C

MATCH void func_801E5738(void) {
    s32 pressed;
    u8  prev_slot;
    u8  slot;

    Menu_DrawClutStrip(g_WindowClut);
    MENU_DRAW_HEADER();
    UI_TextDraw(28, 21, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0xAC));
    SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 1U);
    pressed   = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown));
    prev_slot = g_SaveSlotFirst;
    if (pressed & PADLup) {
        slot            = prev_slot - 1;
        g_SaveSlotFirst = slot;
        if ((s8)slot < 0) {
            g_SaveSlotFirst = g_SaveSlotCount - 1;
        }
    } else {
        if (pressed & PADLdown) {
            g_SaveSlotFirst = prev_slot + 1;
            if ((g_SaveSlotFirst & BYTE_MASK) >= g_SaveSlotCount) {
                g_SaveSlotFirst = 0;
            }
        }
    }
    if (prev_slot != g_SaveSlotFirst) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*(&g_SaveSlots[0].bytes.card_index + (g_SaveSlotFirst * SHOP_SLOT_STRIDE)) != GAME_NONE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            D_8014865B = 1;
            g_MenuCampStep++;
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_MenuCampStep = 0xC;
    }
}
