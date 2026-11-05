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

    character  = g_CharSlot[D_80144F5A[party_slot & BYTE_MASK]];
    record     = &g_Characters[character];
    slots[0]   = &record->equipment.weapon;
    slots[1]   = &record->equipment.shield;
    slots[2]   = &record->equipment.helmet;
    slots[3]   = &record->equipment.armor;
    D_801ED63C = *slots[0];
    best       = g_Weapons[*slots[0]].stats.power;
    for (i = 0; i < 128; i++) {
        item  = D_801C8940[i];
        power = g_Weapons[item].stats.power;
        if ((((Item_GetEquipability(ITEM_CAT_WEAPON, item) & BYTE_MASK) >> character) & 1) &&
            (((best & HALF_MASK) < (power & HALF_MASK)) ||
             (((best & HALF_MASK) == (power & HALF_MASK)) && (item < D_801ED63C)))) {
            D_801ED63C = item;
            best       = power;
        }
    }
    for (i = 1; i < 4; i++) {
        (&D_801ED63C)[i] = *slots[i];
        best             = g_Armors[(&D_801ED63C)[i]].stats.power;
        for (j = 0; j < 128; j++) {
            item  = D_801C8944[j];
            power = g_Armors[item].stats.power;
            if ((g_Armors[item].equip_type == i + 1) &&
                (((Item_GetEquipability(ITEM_CAT_ARMOR, item) & BYTE_MASK) >> character) & 1) &&
                (((best & HALF_MASK) < (power & HALF_MASK)) ||
                 (((best & HALF_MASK) == (power & HALF_MASK)) && (item < (&D_801ED63C)[i])))) {
                (&D_801ED63C)[i] = item;
                best             = power;
            }
        }
    }
    D_801ED640 = record->equipment.accessories[0];
    D_801ED641 = record->equipment.accessories[1];
}
#else
INCLUDE_ASM(func_801D67D8);
#endif
