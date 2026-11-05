#include "shop_00.h"

/* func_801D3828 */
MATCH void Shop_Equip(u8 character_id, u8 slot, u8 item_id) {
    Character* character;

    character = &g_Characters[character_id];
    switch (slot) {
        default:
        case EQUIP_SLOT_WEAPON:
            Item_Remove(ITEM_CAT_WEAPON, item_id, 1, 0);
            Item_Add(ITEM_CAT_WEAPON, character->equipment.weapon, 1, 0);
            character->equipment.weapon = item_id;
            break;
        case EQUIP_SLOT_SHIELD:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equipment.shield, 1, 0);
            character->equipment.shield = item_id;
            break;
        case EQUIP_SLOT_HELMET:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equipment.helmet, 1, 0);
            character->equipment.helmet = item_id;
            break;
        case EQUIP_SLOT_ARMOR:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equipment.armor, 1, 0);
            character->equipment.armor = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            Item_Remove(ITEM_CAT_ACCESSORY, item_id, 1, 0);
            Item_Add(ITEM_CAT_ACCESSORY, character->equipment.accessories[0], 1, 0);
            character->equipment.accessories[0] = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            Item_Remove(ITEM_CAT_ACCESSORY, item_id, 1, 0);
            Item_Add(ITEM_CAT_ACCESSORY, character->equipment.accessories[1], 1, 0);
            character->equipment.accessories[1] = item_id;
            break;
    }
}
