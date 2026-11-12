#include "engine/slus/slus.h"

MATCH bool Char_TestAbilityRole(s32 bit, s32 role, ItemCategory category, s32 item_id) {
    s32 equip_slot;

    switch (Item_GetIcon(category & BYTE_MASK, item_id & BYTE_MASK) & BYTE_MASK) {
        case 1:
            equip_slot = 0;
            break;
        case 2:
            equip_slot = 1;
            break;
        case 3:
            equip_slot = 2;
            break;
        case 4:
            equip_slot = 3;
            break;
        case 5:
            equip_slot = 4;
            break;
        default:
            return 0;
    }
    if ((((Item_GetEquipability(category & BYTE_MASK, item_id & BYTE_MASK) & BYTE_MASK) >> bit) & 0x1) != 0) {
        if ((equip_slot & BYTE_MASK) < 4u && (equip_slot & BYTE_MASK) == (role & BYTE_MASK)) {
            return 1;
        }
        if ((equip_slot & BYTE_MASK) == 4 && ((role & BYTE_MASK) == (equip_slot & BYTE_MASK) || (role & BYTE_MASK) == 5)) {
            return 1;
        }
    }
    return 0;
}
