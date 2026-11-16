#include "shop_00.h"

/* Takes the item from the inventory and puts the worn one back in its place. */
#define SHOP_SWAP_EQUIPMENT(category, equip_slot)          \
    Item_Remove(category, item_id, 1, 0);                  \
    Item_Add(category, character->equip.equip_slot, 1, 0); \
    character->equip.equip_slot = item_id

/* func_801D3828 */
MATCH void Shop_Equip(u8 character_id, u8 slot, u8 item_id) {
    Character* character;

    character = &g_Characters[character_id];
    switch (slot) {
        default:
        case EQUIP_SLOT_WEAPON:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_WEAPON, weapon);
            break;
        case EQUIP_SLOT_SHIELD:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_ARMOR, shield);
            break;
        case EQUIP_SLOT_HELMET:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_ARMOR, helmet);
            break;
        case EQUIP_SLOT_ARMOR:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_ARMOR, armor);
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_ACCESSORY, accessories[0]);
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            SHOP_SWAP_EQUIPMENT(ITEM_CAT_ACCESSORY, accessories[1]);
            break;
    }
}
