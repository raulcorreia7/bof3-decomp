#include "start_08.h"
#include "menu/inventory.h"

/* func_801D67D8 */
MATCH void Menu_PreviewStrongestEquipment(u8 character) {
    Character* record;
    u8*        slots[EQUIP_SLOT_ARMOR + 1];
    Armor*     armor;
    u8         item;
    u16        power;
    u16        best;
    u8         i;
    u8         j;

    character = g_CharSlot[g_PartyFieldOrder[character]];
    record    = &g_Characters[character];

    slots[EQUIP_SLOT_WEAPON] = &record->equip.weapon;
    slots[EQUIP_SLOT_SHIELD] = &record->equip.shield;
    slots[EQUIP_SLOT_HELMET] = &record->equip.helmet;
    slots[EQUIP_SLOT_ARMOR]  = &record->equip.armor;

    g_EquipPreview[EQUIP_SLOT_WEAPON] = *slots[EQUIP_SLOT_WEAPON];
    best                              = g_Weapons[g_EquipPreview[EQUIP_SLOT_WEAPON]].power;
    for (i = 0; i < INV_SLOTS_PER_CATEGORY; i++) {
        item  = D_801C893C[ITEM_CAT_WEAPON][i];
        power = g_Weapons[item].power;
        if (((Item_GetEquipability(ITEM_CAT_WEAPON, item) >> character) & 0x1) && (best < power || (best == power && item < g_EquipPreview[EQUIP_SLOT_WEAPON]))) {
            g_EquipPreview[EQUIP_SLOT_WEAPON] = item;
            best                              = g_Weapons[item].power;
        }
    }

    for (i = EQUIP_SLOT_SHIELD; i <= EQUIP_SLOT_ARMOR; i++) {
        g_EquipPreview[i] = *slots[i];
        best              = g_Armors[g_EquipPreview[i]].power;
        for (j = 0; j < INV_SLOTS_PER_CATEGORY; j++) {
            item  = D_801C893C[ITEM_CAT_ARMOR][j];
            armor = &g_Armors[item];
            power = armor->power;
            if (armor->equip_type == ARMOR_TYPE_OF_SLOT(i) && ((Item_GetEquipability(ITEM_CAT_ARMOR, item) >> character) & 0x1) && (best < power || (best == power && item < g_EquipPreview[i]))) {
                g_EquipPreview[i] = item;
                best              = g_Armors[item].power;
            }
        }
    }

    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = record->equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = record->equip.accessories[1];
}
