#include "start_08.h"
#include "menu/inventory.h"

/* Picks the lightest item of each equipment slot, breaking ties by the higher
 * power and then the lower id. */
MATCH void func_801D6AC4(u8 character) {
    Character* record;
    u8*        slots[EQUIP_SLOT_ARMOR + 1];
    Armor*     armor;
    u8         item;
    u8         weight;
    u16        power;
    u8         bestWeight;
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
    bestWeight                        = g_Weapons[g_EquipPreview[EQUIP_SLOT_WEAPON]].weight;
    for (i = 0; i < INV_SLOTS_PER_CATEGORY; i++) {
        item   = D_801C8940[i];
        power  = g_Weapons[item].power;
        weight = g_Weapons[item].weight;
        if (((Item_GetEquipability(ITEM_CAT_WEAPON, item) >> character) & 0x1) &&
            (g_EquipPreview[EQUIP_SLOT_WEAPON] == 0 || bestWeight > weight || (bestWeight == weight && (best < power || (best == power && item < g_EquipPreview[EQUIP_SLOT_WEAPON]))))) {
            g_EquipPreview[EQUIP_SLOT_WEAPON] = item;
            best                              = g_Weapons[item].power;
            bestWeight                        = g_Weapons[item].weight;
        }
    }

    for (i = EQUIP_SLOT_SHIELD; i <= EQUIP_SLOT_ARMOR; i++) {
        g_EquipPreview[i] = *slots[i];
        best              = g_Armors[g_EquipPreview[i]].power;
        bestWeight        = g_Armors[g_EquipPreview[i]].weight;
        for (j = 0; j < INV_SLOTS_PER_CATEGORY; j++) {
            item   = D_801C8944[j];
            armor  = &g_Armors[item];
            power  = armor->power;
            weight = armor->weight;
            if (armor->type - ITEM_TYPE_SHIELD == i - EQUIP_SLOT_SHIELD && ((Item_GetEquipability(ITEM_CAT_ARMOR, item) >> character) & 0x1) &&
                (g_EquipPreview[i] == 0 || bestWeight > weight || (bestWeight == weight && (best < power || (best == power && item < g_EquipPreview[EQUIP_SLOT_WEAPON]))))) {
                g_EquipPreview[i] = item;
                /* Retail reloads the weight into the power value here. */
                best              = g_Armors[item].weight;
                bestWeight        = g_Armors[item].weight;
            }
        }
    }

    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = record->equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = record->equip.accessories[1];
}
