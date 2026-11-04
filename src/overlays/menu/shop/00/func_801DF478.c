#include "shop_00.h"

MATCH s32 func_801DF478(void) {
    u8  field_id;
    u8  standby_id;
    u8  slot;
    s32 record_off;

    if (D_80148658 == D_8014865A) {
        if (D_80148658 == 0) {
            Menu_SwapBytes_801DF464(&D_80144F5A[D_80148659], &D_80144F5A[(s8)D_8014865D]);
        } else {
            Menu_SwapBytes_801DF464(&D_801E6244[D_80148659], &D_801E6244[(s8)D_8014865D]);
        }
        return 0xFF;
    }
    if (D_80148658 == 0) {
        field_id   = D_80144F5A[D_80148659];
        standby_id = D_801E6244[(s8)D_8014865D];
    } else {
        field_id   = D_80144F5A[(s8)D_8014865D];
        standby_id = D_801E6244[D_80148659];
    }
    record_off = g_CharSlot[field_id] * 0xA4;
    if (((u8*)&g_Characters[0].unk_07)[record_off] & 2) {
        return field_id;
    }
    record_off = g_CharSlot[standby_id] * 0xA4;
    if (((u8*)&g_Characters[0].unk_07)[record_off] & 2) {
        return standby_id;
    }
    SND_PlayCue(EMI_CUE_ID(1, 3));
    for (slot = 0; slot < (Party_CountOrder(0) & BYTE_MASK); slot++) {
        if (D_80144F5A[slot] == field_id) {
            D_80144F5A[slot] = standby_id;
        }
        if (D_80144F5D[slot] == field_id) {
            D_80144F5D[slot] = standby_id;
        }
    }
    for (slot = 0; slot < D_801E6250; slot++) {
        if (D_801E6244[slot] == standby_id) {
            D_801E6244[slot] = field_id;
        }
    }
    return 0xFF;
}
