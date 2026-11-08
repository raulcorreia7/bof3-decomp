#include "sisyou_00.h"

void Menu_DrawStatPanel(s32 id, s32 y, u8 entry);

/* Stock list (stride 0x140 per entry) and item count. */

MATCH void func_801D0C88(void) {
    s32 count;
    s32 row;
    u8* entryp;
    u16 y;
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);

    g_MenuMasterScrollOffset -= 1;
    row   = 0;
    count = g_PartySize;
    if (count > 0) {
        entryp = &g_Game.members[0].character_index;
        y      = MASTER_MENU_ROW_TOP;
        do {
            Menu_DrawMasterPartyRow((MASTER_MENU_ROW_X - (g_MenuMasterScrollOffset * 36)) & HALF_MASK, y, *entryp, row);
            Menu_DrawStatPanel((g_MenuMasterScrollOffset * 40) + MASTER_MENU_STAT_PANEL_X, y, *entryp);
            entryp += BATTLE_PARTY_STRIDE;
            y += MASTER_MENU_ROW_PITCH;
            row++;
        } while (row < g_Game.party_size);
    }
    Menu_DrawHeaderBar(MASTER_MENU_FRAME_X, (MASTER_MENU_FRAME_Y - (g_MenuMasterScrollOffset * 10)) & 0xFFFE,
                       MASTER_MENU_FRAME_WIDTH, MASTER_MENU_FRAME_HEIGHT, g_WindowStyle);
    if (g_MenuMasterScrollOffset == 0) {
        g_MenuMasterCursor = 0;
        g_MenuMasterSubStep += 1;
    }
}
