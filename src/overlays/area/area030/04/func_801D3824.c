#include "area030_04.h"

/* Runs the panel helper, then issues the 0x1D text-row draw for
 * the fixed row selected by the scratch record byte at +0x4B. */
MATCH void func_801D3824(void) {
    u8* record;
    s32 index;

    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    record = (u8*)g_Task;
    index  = (record[0x4B] * 3) << 2;
    UI_DrawText(0x1D, 0x14, 0, D_801E1E78[index], (u8*)(*(u32*)((u8*)D_801E1E7C + index)));
}
