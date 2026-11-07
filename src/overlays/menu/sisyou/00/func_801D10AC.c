#include "sisyou_00.h"

void Menu_DrawStatPanel(s32 id, s32 y, u8 entry);

/* Stock list (stride 0x140 per entry). */

MATCH void func_801D10AC(u32 message_id) {
    u16* padp;
    s32  trig;
    u16  pad;
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);
    s32 count;
    u8  handler;
    s32 i;
    u8* entryp;
    u16 y;

    padp = &g_InputPressed;
    trig = INPUT_REPEATED(*padp, (PADLright | PADLleft));
    pad  = *padp;

    if (pad & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        if (g_MasterBannerLock != 0) {
            handler = g_MasterSubStep - 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 2));
            handler = g_MasterSubStep + 1;
        }
        g_MasterSubStep = handler;
        SND_PlayCue(EMI_CUE_ID(1, 4));
    } else if (pad & g_InputMasks[INPUT_SLOT_CANCEL]) {
        g_MasterBannerLock = 1;
        g_MasterSubStep    = g_MasterSubStep - 1;
        SND_PlayCue(EMI_CUE_ID(1, 6));
    } else if (trig & HALF_MASK) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        g_MasterBannerLock ^= 1;
    }

    count = g_PartySize;
    i     = 0;
    if (count > 0) {
        entryp = D_80145FCC.bytes;
        y      = MASTER_MENU_ROW_TOP;
        do {
            Master_DrawPartyRow(MASTER_MENU_ROW_X, y, *entryp, i);
            Menu_DrawStatPanel(MASTER_MENU_STAT_PANEL_X, y, *entryp);
            entryp += BATTLE_PARTY_STRIDE;
            y += MASTER_MENU_ROW_PITCH;
            i++;
        } while (i < g_PartySize);
    }

    MenuDrawSelectionBox(MASTER_MENU_ROW_X, (g_MasterMenuCursor * MASTER_MENU_ROW_PITCH + MASTER_MENU_ROW_TOP) & 0xFFFE,
                         MASTER_MENU_SELECT_WIDTH, MASTER_MENU_SELECT_HEIGHT, 0, 6);
    Menu_DrawHeaderBar(MASTER_MENU_FRAME_X, MASTER_MENU_FRAME_Y, MASTER_MENU_FRAME_WIDTH, MASTER_MENU_FRAME_HEIGHT,
                       g_WindowStyle);
    i = MASTER_MENU_TEXT_BANK + (message_id & HALF_MASK) * 2;
    UI_DrawText(MASTER_MENU_TEXT_X, MASTER_MENU_TEXT_Y, 0, 255, (u8*)(MEM(u16, i) + MASTER_MENU_TEXT_BANK));
    Menu_DrawCursorSprite((g_MasterBannerLock << 5) + 0xF3, 0x15, 0);
}
