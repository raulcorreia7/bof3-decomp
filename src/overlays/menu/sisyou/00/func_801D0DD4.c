#include "sisyou_00.h"

void Menu_DrawStatPanel(s32 id, s32 y, u8 entry);

/* Stock list (stride 0x140 per entry) and the character records' master id
 * byte at +0x1B (stride 0xA4). */

MATCH void func_801D0DD4(s32 message_id, s32 confirm) {
    u16* padp;
    s32  trig;
    u16  pad;
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);
    s32 count;
    u8  item;
    s32 sel;
    s32 i;
    u8* entryp;
    u16 y;

    padp = &g_InputPressed;
    trig = INPUT_REPEATED(*padp, (PADLup | PADLdown));
    pad  = *padp;

    if (pad & D_80145AC2) {
        item = D_80145FCC.bytes[g_MasterMenuCursor * BATTLE_PARTY_STRIDE];
        if (g_Characters[item].master_id == D_801448ED) {
            if ((confirm & BYTE_MASK) == 0) {
                goto play_stop; /* both row-state cases share this exit */
            }
        } else {
            if ((confirm & BYTE_MASK) != 0) {
                goto play_stop; /* the complementary row state takes the same exit */
            }
        }
        SND_PlayCue(EMI_CUE_ID(1, 4));
        g_MasterSubStep += 1;
        g_MasterBannerLock = 0;
        goto after_input; /* stock cue queued: skip the cursor/selection block */
    play_stop:
        SND_PlayCue(EMI_CUE_ID(1, 7));
    } else if (pad & D_80145AC4) {
        g_MasterBannerLock = 1;
        SND_PlayCue(EMI_CUE_ID(1, 2));
        SND_PlayCue(EMI_CUE_ID(1, 6));
        g_MasterSubStep = 4;
    } else {
        if (trig & PADLup) {
            sel = g_MasterMenuCursor;
            if (sel == 0) {
                sel = g_PartySize;
            }
            g_MasterMenuCursor = sel - 1;
            SND_PlayCue(EMI_CUE_ID(1, 0));
        } else if (trig & PADLdown) {
            if ((g_MasterMenuCursor & BYTE_MASK) == g_PartySize - 1) {
                g_MasterMenuCursor = 0;
            } else {
                g_MasterMenuCursor = g_MasterMenuCursor + 1;
            }
            SND_PlayCue(EMI_CUE_ID(1, 0));
        }
    }
after_input:
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
                         MASTER_MENU_SELECT_WIDTH, MASTER_MENU_SELECT_HEIGHT, 1, 6);
    Menu_DrawHeaderBar(MASTER_MENU_FRAME_X, MASTER_MENU_FRAME_Y, MASTER_MENU_FRAME_WIDTH, MASTER_MENU_FRAME_HEIGHT,
                       D_80144952);
    i = MASTER_MENU_TEXT_BANK + (message_id & HALF_MASK) * 2;
    UI_DrawText(MASTER_MENU_TEXT_X, MASTER_MENU_TEXT_Y, 0, 255, (u8*)(MEM(u16, i) + MASTER_MENU_TEXT_BANK));
}
