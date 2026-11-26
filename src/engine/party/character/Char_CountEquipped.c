#include "engine/game/00/game_00.h"

/* func_801C38F4 */
/* Counts the character's equipment slots of a group (weapon, shield/helmet/armor, accessories) that hold the item id. */
MATCH s32 Char_CountEquipped(s32 character_index, s32 equip_group, s32 item_id) {
    Character* record;
    s32        group;
    s32        target;
    s32        count;

    group  = equip_group & BYTE_MASK;
    count  = character_index & BYTE_MASK;
    record = &g_Characters[g_CharSlot[count]];
    count  = 0;
    if (group == EQUIP_GROUP_WEAPON) {
        goto weapon;
    }
    if (group < EQUIP_GROUP_ARMOR) {
        goto done;
    }
    if (group == EQUIP_GROUP_ARMOR) {
        goto armor;
    }
    if (group == EQUIP_GROUP_ACCESSORY) {
        goto accessory;
    }
    goto done;
weapon:
    if (record->equip.weapon == (item_id & BYTE_MASK)) {
        count = 1;
    }
    goto done;
armor:
    target = item_id & BYTE_MASK;
    if (record->equip.shield == target) {
        count = 1;
    }
    if (record->equip.helmet == target) {
        count += 1;
    }
    if (record->equip.armor == target) {
        count += 1;
    }
    goto done;
accessory:
    target = item_id & BYTE_MASK;
    if (record->equip.accessories[0] == target) {
        count = 1;
    }
    if (record->equip.accessories[1] == target) {
        count += 1;
    }
done:
    return count & BYTE_MASK;
}
