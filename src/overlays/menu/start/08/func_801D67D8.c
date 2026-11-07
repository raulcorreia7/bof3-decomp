#include "start_08.h"

/* 88.2%; first difference at the prologue: retail frame 0x50, ours 0x48. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D67D8(u8 party_slot) {
    Character* record;
    u8*        slots[4];
    u8         character;
    u8         item;
    u8         power;
    u8         best;
    u8         i;
    u8         j;

    character                         = g_CharSlot[g_PartyFieldOrder[party_slot & BYTE_MASK]];
    record                            = &g_Characters[character];
    slots[0]                          = &record->equip.weapon;
    slots[1]                          = &record->equip.shield;
    slots[2]                          = &record->equip.helmet;
    slots[3]                          = &record->equip.armor;
    g_EquipPreview[EQUIP_SLOT_WEAPON] = *slots[0];
    best                              = g_Weapons[*slots[0]].stats.power;
    for (i = 0; i < 128; i++) {
        item  = D_801C8940[i];
        power = g_Weapons[item].stats.power;
        if ((((Item_GetEquipability(ITEM_CAT_WEAPON, item) & BYTE_MASK) >> character) & 1) &&
            (((best & HALF_MASK) < (power & HALF_MASK)) ||
             (((best & HALF_MASK) == (power & HALF_MASK)) && (item < g_EquipPreview[EQUIP_SLOT_WEAPON])))) {
            g_EquipPreview[EQUIP_SLOT_WEAPON] = item;
            best                              = power;
        }
    }
    for (i = 1; i < 4; i++) {
        g_EquipPreview[i] = *slots[i];
        best              = g_Armors[g_EquipPreview[i]].stats.power;
        for (j = 0; j < 128; j++) {
            item  = D_801C8944[j];
            power = g_Armors[item].stats.power;
            if ((g_Armors[item].equip_type == i + 1) &&
                (((Item_GetEquipability(ITEM_CAT_ARMOR, item) & BYTE_MASK) >> character) & 1) &&
                (((best & HALF_MASK) < (power & HALF_MASK)) ||
                 (((best & HALF_MASK) == (power & HALF_MASK)) && (item < g_EquipPreview[i])))) {
                g_EquipPreview[i] = item;
                best              = power;
            }
        }
    }
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = record->equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = record->equip.accessories[1];
}
#else
/* Needs Weapon.power and Armor.power; first difference at +0x6C. */
INCLUDE_ASM(func_801D67D8);
#endif
