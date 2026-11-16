#include "area030_04.h"

/* Draws the equipment column of the area030 status screen: the two equipment
 * rows' icons and names and the guide message. */
MATCH void func_801D88E0(s16 x, s16 y) {
    s16 x0;
    s16 y0;
    u16 guide;

    x0 = x;
    y0 = y;
    func_801D8D70(x, y);
    UI_DrawText((s16)(x + 51), (s16)(y + 7), 0, 5U, D_801E21D4);
    if (g_Task->option_flags & 0x80) {
        u8* rod;

        rod = &g_FishingRod;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 26), 0, 0xCU, (u8*)&g_OptionItems[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingLure, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 42), 0, 0xCU, (u8*)&g_OptionItems[g_FishingLure]);
    } else if ((g_Task->option_flags & 1) == 0) {
        u8* rod;

        rod = &g_FishingRod;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 1);
        UI_DrawText((s16)(x + 28), (s16)(y + 26), 7, 0xCU, (u8*)&g_OptionItems[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 26), *rod, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 24), g_Task->option_flags, 0xCU, (u8*)&g_OptionItems[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingLure, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 42), 0, 0xCU, (u8*)&g_OptionItems[g_FishingLure]);
    } else {
        u8* rod;

        rod = &g_FishingRod;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 26), 0, 0xCU, (u8*)&g_OptionItems[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingLure, 3, 1);
        UI_DrawText((s16)(x + 28), (s16)(y + 42), 7, 0xCU, (u8*)&g_OptionItems[g_FishingLure]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 42), g_FishingLure, 3, 0);
        UI_DrawText((s16)(x + 28), (s16)(y + 40), g_Task->option_flags & ACTOR_OPT_KEEP_FACING, 0xCU, (u8*)&g_OptionItems[g_FishingLure]);
    }
    UI_DrawText((s16)(x0 + 51), (s16)(y0 + 71), 0, 5U, D_801E21D9);
    guide = g_Task->unk_2C;
    if (guide != 0xFFFF) {
        UI_DrawText(25, 154, 0, 0xFFU, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, guide));
    }
}
