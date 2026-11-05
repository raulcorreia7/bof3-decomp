#include "start_08.h"

MATCH void func_801D6FBC(void) {
    s32 record;
    s32 record_index;
    u8  index;
    s32 bit_index;

    index     = D_80148535;
    bit_index = g_CharSlot[D_80144F5A[D_80148510]];
    if (((s32)(Item_GetEquipability(D_80148530, index) & BYTE_MASK) >> bit_index) & 1) {
        D_80148511   = 0;
        record_index = bit_index & BYTE_MASK;
    } else {
        D_80148511   = 1;
        record_index = bit_index & BYTE_MASK;
    }
    record                    = record_index;
    D_801ED63C                = g_Characters[record].equipment.weapon;
    D_801ED63D                = g_Characters[record].equipment.shield;
    D_801ED63E                = g_Characters[record].equipment.helmet;
    D_801ED63F                = g_Characters[record].equipment.armor;
    D_801ED640                = g_Characters[record].equipment.accessories[0];
    D_801ED641                = g_Characters[record].equipment.accessories[1];
    (&D_801ED63C)[D_8014850E] = index;
}
