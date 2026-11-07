#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D67D8(u8 party_slot) {
    Character* record;
    u8*        slots[4];
    u8         character;
    u8         item;
    u16        power;
    u16        best;
    u8         i;
    u8         j;

    character                         = g_CharSlot[g_PartyFieldOrder[party_slot & BYTE_MASK]];
    record                            = &g_Characters[character];
    slots[0]                          = &record->equip.weapon;
    slots[1]                          = &record->equip.shield;
    slots[2]                          = &record->equip.helmet;
    slots[3]                          = &record->equip.armor;
    item                              = *slots[0];
    g_EquipPreview[EQUIP_SLOT_WEAPON] = item;
    best                              = g_Weapons[item].power;
    for (i = 0; i < 128; i++) {
        item  = D_801C8940[i];
        power = g_Weapons[item].power;
        if ((((Item_GetEquipability(ITEM_CAT_WEAPON, item) & BYTE_MASK) >> character) & 1) &&
            ((best < power) || ((best == power) && (item < g_EquipPreview[EQUIP_SLOT_WEAPON])))) {
            g_EquipPreview[EQUIP_SLOT_WEAPON] = item;
            best                              = g_Weapons[item].power;
        }
    }
    for (i = 1; i < 4; i++) {
        g_EquipPreview[i] = *slots[i];
        best              = g_Armors[g_EquipPreview[i]].power;
        for (j = 0; j < 128; j++) {
            item  = D_801C8944[j];
            power = g_Armors[item].power;
            if ((g_Armors[item].equip_type == i + 1) &&
                (((Item_GetEquipability(ITEM_CAT_ARMOR, item) & BYTE_MASK) >> character) & 1) &&
                ((best < power) || ((best == power) && (item < g_EquipPreview[i])))) {
                g_EquipPreview[i] = item;
                best              = g_Armors[item].power;
            }
        }
    }
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = record->equip.accessories[0];
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = record->equip.accessories[1];
}
#else
/* 0x50 frame matches; first difference +0x44: retail loads the record's equip byte into s8, ours into v0. */
INCLUDE_ASM(func_801D67D8);
#endif
