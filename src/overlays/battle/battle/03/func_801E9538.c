#include "battle_03.h"

extern u32 D_801EB4F4[][3];
extern u8  D_801EB4FA[][12];

MATCH void func_801E9538(void) {
    u8 index;
    u8 count;

    index = BATTLE_PANEL_TASK->cell_0A.slot;
    count = func_801EAB6C((u8*)D_801EB4F4[index][0]);
    func_801D8270((s16)g_MenuCurrentPanel->x - 0x10, (s16)g_MenuCurrentPanel->y);
    index = BATTLE_PANEL_TASK->cell_0A.slot;
    UI_DrawText((g_MenuCurrentPanel->x - count * 4 + 38), (g_MenuCurrentPanel->y + 3), D_801EB4FA[index][0],
                0x12u, (u8*)D_801EB4F4[index][0]);
}
