#include "sisyou_00.h"

void Menu_DrawStatPanel(s32 id, s32 y, u8 entry);

/* Stock list (stride 0x140 per entry) and the character records' master id byte at +0x1B (stride 0xA4). */

MATCH void func_801D0DD4(s32 message_id, s32 confirm) {
    u16* padp;
    s32  trig;
    u16  pad;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);
    s32 count;
    u8  item;
    s32 sel;
    s32 i;
    u8* entryp;
    u16 y;

    padp = &g_InputPressed;
    trig = INPUT_REPEATED(*padp, (PADLup | PADLdown));
    pad  = *padp;

    if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        item = g_Game.members[g_MenuMasterCursor].character_index;
        if (g_Characters[item].master_id == g_SceneEventSelection) {
            if ((confirm & BYTE_MASK) == 0) {
                goto play_stop; /* both row-state cases share this exit */
            }
        } else {
            if ((confirm & BYTE_MASK) != 0) {
                goto play_stop; /* the complementary row state takes the same exit */
            }
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
        g_MenuMasterSubStep += 1;
        g_MenuMasterBannerLock = 0;
        goto after_input; /* stock cue queued: skip the cursor/selection block */
    play_stop:
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        g_MenuMasterBannerLock = 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_MenuMasterSubStep = 4;
    } else {
        if (trig & PADLup) {
            sel = g_MenuMasterCursor;
            if (sel == 0) {
                sel = g_Game.party_size;
            }
            g_MenuMasterCursor = sel - 1;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        } else if (trig & PADLdown) {
            if ((g_MenuMasterCursor & BYTE_MASK) == g_Game.party_size - 1) {
                g_MenuMasterCursor = 0;
            } else {
                g_MenuMasterCursor = g_MenuMasterCursor + 1;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        }
    }
after_input:
    count = g_PartySize;
    i     = 0;
    if (count > 0) {
        entryp = &g_Game.members[0].character_index;
        y      = MASTER_MENU_ROW_TOP;
        do {
            Menu_DrawMasterPartyRow(MASTER_MENU_ROW_X, y, *entryp, i);
            Menu_DrawStatPanel(MASTER_MENU_STAT_PANEL_X, y, *entryp);
            entryp += BATTLE_PARTY_STRIDE;
            y += MASTER_MENU_ROW_PITCH;
            i++;
        } while (i < g_Game.party_size);
    }

    Menu_DrawSelectionBox(MASTER_MENU_ROW_X,
                          (g_MenuMasterCursor * MASTER_MENU_ROW_PITCH + MASTER_MENU_ROW_TOP) & 0xFFFE,
                          MASTER_MENU_SELECT_WIDTH, MASTER_MENU_SELECT_HEIGHT, 1, 6);
    Menu_DrawHeaderBar(MASTER_MENU_FRAME_X, MASTER_MENU_FRAME_Y, MASTER_MENU_FRAME_WIDTH, MASTER_MENU_FRAME_HEIGHT,
                       g_WindowStyle);
    /* MESSAGE_TABLE_TEXT here changes the stock-row loop's register allocation. */
    i = (s32)&AREA_MESSAGE_TABLE->offsets[message_id & HALF_MASK];
    UI_DrawText(MASTER_MENU_TEXT_X, MASTER_MENU_TEXT_Y, 0, 255, (u8*)(MEM(u16, i) + (u32)AREA_MESSAGE_TABLE));
}
