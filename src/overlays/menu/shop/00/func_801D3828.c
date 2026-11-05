#include "shop_00.h"

/* Defined by the main executable; this target has no prototype. */

MATCH void func_801D3828(u8 record, u8 row, u8 color) {
    Character* rec;

    rec = &g_Characters[record];
    switch (row) {
        default:
        case 0:
            Item_Remove(1, color, 1, 0);
            Item_Add(ITEM_CAT_WEAPON, rec->weapon, 1, 0);
            rec->weapon = color;
            break;
        case 1:
            Item_Remove(2, color, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, rec->shield, 1, 0);
            rec->shield = color;
            break;
        case 2:
            Item_Remove(2, color, 1, 0);
            Item_Add(2, rec->helmet, 1, 0);
            rec->helmet = color;
            break;
        case 3:
            Item_Remove(2, color, 1, 0);
            Item_Add(2, rec->armor, 1, 0);
            rec->armor = color;
            break;
        case 4:
            Item_Remove(3, color, 1, 0);
            Item_Add(ITEM_CAT_ACCESSORY, rec->accessories[0], 1, 0);
            rec->accessories[0] = color;
            break;
        case 5:
            Item_Remove(3, color, 1, 0);
            Item_Add(3, rec->accessories[1], 1, 0);
            rec->accessories[1] = color;
            break;
    }
}
