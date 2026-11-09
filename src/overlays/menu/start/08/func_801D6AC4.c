#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D6AC4(s32 party_slot) {
    struct {
        u8* slots[4];
        u8* record;
        s32 value;
    } frame;

    s32    val0;
    s32    val1;
    s32    val2;
    s32    val3;
    u32    tmp4;
    u32    tmp5;
    u32    tmp6;
    u32    tmp7;
    u32    tmp8;
    u32    tmp9;
    u32    tmp10;
    u32    tmp11;
    u8     tmp12;
    u8     tmp13;
    u8     tmp14;
    u8     val4;
    u8     val5;
    u8     val6;
    u8     val7;
    u8     val8;
    u8     val9;
    u8     val10;
    Armor* armor;

    val4                              = g_CharSlot[g_PartyFieldOrder[party_slot & BYTE_MASK]];
    frame.record                      = &g_Characters[val4 & BYTE_MASK];
    frame.slots[0]                    = frame.record + 0xE;
    frame.slots[1]                    = frame.record + 0xF;
    frame.slots[2]                    = frame.record + 0x10;
    frame.slots[3]                    = frame.record + 0x11;
    tmp14                             = FIELD(u8, frame.record, 0xEu);
    val3                              = 0;
    g_EquipPreview[EQUIP_SLOT_WEAPON] = tmp14;
    val5                              = g_Weapons[tmp14].power;
    val10                             = g_Weapons[tmp14].weight;
    do {
        val8        = D_801C8940[val3 & BYTE_MASK];
        val6        = val8 & BYTE_MASK;
        val9        = g_Weapons[val6].power;
        val7        = g_Weapons[val6].weight;
        frame.value = (s32)val4;
        if ((((s32)(Item_GetEquipability(ITEM_CAT_WEAPON, val6) & BYTE_MASK) >> val4) & 1) &&
            ((tmp7 = val10 & BYTE_MASK, (g_EquipPreview[EQUIP_SLOT_WEAPON] == 0)) || (tmp11 = val7 & BYTE_MASK, ((tmp11 < tmp7) != 0)) ||
             ((tmp4 = val5 & HALF_MASK, (tmp7 == tmp11)) && ((tmp8 = val9 & HALF_MASK, ((tmp4 < tmp8) != 0)) || ((tmp4 == tmp8) && (val6 < (u8)g_EquipPreview[EQUIP_SLOT_WEAPON])))))) {
            g_EquipPreview[EQUIP_SLOT_WEAPON] = val8;
            val5                              = g_Weapons[val8].power;
            val10                             = g_Weapons[val8].weight;
        }
        val3 += 1;
    } while ((u32)(val3 & BYTE_MASK) < 0x80U);
    val3 = 1;
    val0 = 1 & BYTE_MASK;
    do {
        val1                 = 0;
        tmp13                = *frame.slots[val0];
        val2                 = val0;
        g_EquipPreview[val2] = tmp13;
        val5                 = g_Armors[tmp13 & BYTE_MASK].power;
        val10                = g_Armors[tmp13 & BYTE_MASK].weight;
    loop_12:
        val8  = D_801C8944[val1 & BYTE_MASK];
        val6  = val8 & BYTE_MASK;
        armor = &g_Armors[val6];
        val9  = armor->power;
        val7  = armor->weight;
        if ((armor->equip_type - 2) == (val2 - 1)) {
            frame.value = (s32)val4;
            if ((((s32)(Item_GetEquipability(ITEM_CAT_ARMOR, val6) & BYTE_MASK) >> val4) & 1) &&
                ((tmp5 = val10 & BYTE_MASK, (g_EquipPreview[val2] == 0)) || (tmp9 = val7 & BYTE_MASK, ((tmp9 < tmp5) != 0)) ||
                 ((tmp6 = val5 & HALF_MASK, (tmp5 == tmp9)) && ((tmp10 = val9 & HALF_MASK, ((tmp6 < tmp10) != 0)) || ((tmp6 == tmp10) && (val6 < (u8)g_EquipPreview[EQUIP_SLOT_WEAPON])))))) {
                g_EquipPreview[val2] = val8;
                tmp12                = g_Armors[val8 & BYTE_MASK].weight;
                val5                 = tmp12 & BYTE_MASK;
                val10                = tmp12;
            }
        }
        val1 += 1;
        if ((u32)(val1 & BYTE_MASK) < 0x80U) {
            goto loop_12; /* retail branch */
        }
        val3 += 1;
        val0 = val3 & BYTE_MASK;
    } while ((u32)(val3 & BYTE_MASK) < 4U);
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_1] = FIELD(u8, frame.record, 0x12u);
    g_EquipPreview[EQUIP_SLOT_ACCESSORY_2] = FIELD(u8, frame.record, 0x13u);
}
#else
INCLUDE_ASM(func_801D6AC4);
#endif
