#include "start_08.h"

/* func_801E8DB4 */
MATCH void Menu_DrawCharacterPanel(MenuPanelTask* task) {
    u8* table;
    u8* order;

    table = g_PartyFieldOrder;
    order = table + task->unk_0B * 3;
    Menu_DrawCharacterWindow((u16)task->pos.vx, (u16)task->pos.vy, g_CharSlot[order[task->unk_0A]], task->unk_0C, 0);
    GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    Menu_DrawPanelIcon((task->pos.vx + 9) & HALF_MASK, (task->pos.vy + 5) & HALF_MASK, (task->unk_0A + 3) & BYTE_MASK, 0x1E, (GetClut(16, STAGE_PALETTE_Y) & HALF_MASK), 128);
}
