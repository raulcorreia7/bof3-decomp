#include "commu00_00.h"

MATCH void func_801F0D3C(u8 task_index, u8 record_kind_index) {
    u32 key_term;
    u32 field_term;

    if (D_801F2928[record_kind_index & BYTE_MASK] != 0) {
        g_Task->unk_06                                        = 1;
        D_80146904[(task_index & BYTE_MASK) * ACTOR_SIZE / 2] = (u16)(D_801F2928[record_kind_index & BYTE_MASK] + 0xD1);
    } else {
        g_Task->unk_06                                        = 5;
        D_80146904[(task_index & BYTE_MASK) * ACTOR_SIZE / 2] = 0xC008;
        g_Task->unk_18                                        = 0;
        key_term                                              = (u32)(VILLAGE_ROOM_SUBTYPE(record_kind_index) << 1);
        field_term     = (u32)(D_801457AA[(record_kind_index & BYTE_MASK) * 8] + 0x11);
        g_Task->unk_1C = key_term + field_term;
    }
}
