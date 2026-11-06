#include "shop_00.h"

/* func_801D3828 */
MATCH void Shop_Equip(u8 character_id, u8 slot, u8 item_id) {
    Character* character;

    character = &g_SaveData.characters[character_id];
    switch (slot) {
        default:
        case EQUIP_SLOT_WEAPON:
            Item_Remove(ITEM_CAT_WEAPON, item_id, 1, 0);
            Item_Add(ITEM_CAT_WEAPON, character->equip.weapon, 1, 0);
            character->equip.weapon = item_id;
            break;
        case EQUIP_SLOT_SHIELD:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equip.shield, 1, 0);
            character->equip.shield = item_id;
            break;
        case EQUIP_SLOT_HELMET:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equip.helmet, 1, 0);
            character->equip.helmet = item_id;
            break;
        case EQUIP_SLOT_ARMOR:
            Item_Remove(ITEM_CAT_ARMOR, item_id, 1, 0);
            Item_Add(ITEM_CAT_ARMOR, character->equip.armor, 1, 0);
            character->equip.armor = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            Item_Remove(ITEM_CAT_ACCESSORY, item_id, 1, 0);
            Item_Add(ITEM_CAT_ACCESSORY, character->equip.accessories[0], 1, 0);
            character->equip.accessories[0] = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            Item_Remove(ITEM_CAT_ACCESSORY, item_id, 1, 0);
            Item_Add(ITEM_CAT_ACCESSORY, character->equip.accessories[1], 1, 0);
            character->equip.accessories[1] = item_id;
            break;
    }
}
