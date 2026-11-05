#include "start_08.h"

/* 87.4%; first difference at +0x3C: retail loads a global address (lui) where ours zeroes s6. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D6AC4(s32 party_slot) {
    struct {
        u8* slots[4];
        u8* record;
        s32 value;
    } frame;

    s32    tmp0;
    s32    tmp1;
    s32    tmp2;
    s32    tmp3;
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

    val4           = g_CharSlot[D_80144F5A[party_slot & BYTE_MASK]];
    frame.record   = &g_Characters[val4 & BYTE_MASK];
    frame.slots[0] = frame.record + 0xE;
    frame.slots[1] = frame.record + 0xF;
    frame.slots[2] = frame.record + 0x10;
    frame.slots[3] = frame.record + 0x11;
    tmp14          = FIELD(u8, frame.record, 0xEu);
    val3           = 0;
    tmp2           = tmp14 * 0x18;
    D_801ED63C     = tmp14;
    val5           = D_801C90EE[tmp2];
    val10          = D_801C90EC[tmp2];
    do {
        val8        = D_801C8940[val3 & BYTE_MASK];
        val6        = val8 & BYTE_MASK;
        tmp3        = val6 * 0x18;
        val9        = D_801C90EE[tmp3];
        val7        = D_801C90EC[tmp3];
        frame.value = (s32)val4;
        if ((((s32)(Item_GetEquipability(ITEM_CAT_WEAPON, val6) & BYTE_MASK) >> val4) & 1) &&
            ((tmp7 = val10 & BYTE_MASK, (D_801ED63C == 0)) || (tmp11 = val7 & BYTE_MASK, ((tmp11 < tmp7) != 0)) ||
             ((tmp4 = val5 & HALF_MASK, (tmp7 == tmp11)) &&
              ((tmp8 = val9 & HALF_MASK, ((tmp4 < tmp8) != 0)) || ((tmp4 == tmp8) && (val6 < (u8)D_801ED63C)))))) {
            tmp0       = val8 * 0x18;
            D_801ED63C = val8;
            val5       = D_801C90EE[tmp0];
            val10      = D_801C90EC[tmp0];
        }
        val3 += 1;
    } while ((u32)(val3 & BYTE_MASK) < 0x80U);
    val3 = 1;
    val0 = 1 & BYTE_MASK;
    do {
        val1                = 0;
        tmp13               = *frame.slots[val0];
        val2                = val0;
        (&D_801ED63C)[val2] = tmp13;
        tmp1                = (tmp13 & BYTE_MASK) * 0x16;
        val5                = D_801C98B4[tmp1];
        val10               = D_801C98B3[tmp1];
    loop_12:
        val8  = D_801C8944[val1 & BYTE_MASK];
        val6  = val8 & BYTE_MASK;
        armor = &g_Armors[val6];
        val9  = armor->power;
        val7  = armor->weight;
        if ((armor->equip_type - 2) == (val2 - 1)) {
            frame.value = (s32)val4;
            if ((((s32)(Item_GetEquipability(ITEM_CAT_ARMOR, val6) & BYTE_MASK) >> val4) & 1) &&
                ((tmp5 = val10 & BYTE_MASK, ((&D_801ED63C)[val2] == 0)) ||
                 (tmp9 = val7 & BYTE_MASK, ((tmp9 < tmp5) != 0)) ||
                 ((tmp6 = val5 & HALF_MASK, (tmp5 == tmp9)) && ((tmp10 = val9 & HALF_MASK, ((tmp6 < tmp10) != 0)) ||
                                                                ((tmp6 == tmp10) && (val6 < (u8)D_801ED63C)))))) {
                (&D_801ED63C)[val2] = val8;
                tmp12               = D_801C98B3[(val8 & BYTE_MASK) * 0x16];
                val5                = tmp12 & BYTE_MASK;
                val10               = tmp12;
            }
        }
        val1 += 1;
        if ((u32)(val1 & BYTE_MASK) < 0x80U) {
            goto loop_12; /* retail branch */
        }
        val3 += 1;
        val0 = val3 & BYTE_MASK;
    } while ((u32)(val3 & BYTE_MASK) < 4U);
    D_801ED640 = FIELD(u8, frame.record, 0x12u);
    D_801ED641 = FIELD(u8, frame.record, 0x13u);
}
#else
INCLUDE_ASM(func_801D6AC4);
#endif
