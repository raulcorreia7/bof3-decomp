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
    UI_TextDraw((s16)(x + 51), (s16)(y + 7), 0, 5U, D_801E21D4);
    if (SELF(Actor)->option_flags & 0x80) {
        u8* rod;

        rod = &g_FishingEquipment.rod_id;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 26), 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingEquipment.lure_id, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 42), 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[g_FishingEquipment.lure_id]);
    } else if ((SELF(Actor)->option_flags & 1) == 0) {
        u8* rod;

        rod = &g_FishingEquipment.rod_id;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 1);
        UI_TextDraw((s16)(x + 28), (s16)(y + 26), UI_TEXT_DIM, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 26), *rod, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 24), SELF(Actor)->option_flags, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingEquipment.lure_id, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 42), 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[g_FishingEquipment.lure_id]);
    } else {
        u8* rod;

        rod = &g_FishingEquipment.rod_id;
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 28), *rod, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 26), 0, ITEM_NAME_LENGTH, (u8*)&g_Accessories[*rod]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 44), g_FishingEquipment.lure_id, 3, 1);
        UI_TextDraw((s16)(x + 28), (s16)(y + 42), UI_TEXT_DIM, ITEM_NAME_LENGTH, (u8*)&g_Accessories[g_FishingEquipment.lure_id]);
        Fishing_ShopDrawItemIcon((s16)(x + 16), (s16)(y + 42), g_FishingEquipment.lure_id, 3, 0);
        UI_TextDraw((s16)(x + 28), (s16)(y + 40), SELF(Actor)->option_flags & ACTOR_OPT_KEEP_FACING, ITEM_NAME_LENGTH, (u8*)&g_Accessories[g_FishingEquipment.lure_id]);
    }
    UI_TextDraw((s16)(x0 + 51), (s16)(y0 + 71), 0, 5U, D_801E21D9);
    guide = SELF(Actor)->unk_2C;
    if (guide != 0xFFFF) {
        UI_TextDraw(25, 154, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, guide));
    }
}
