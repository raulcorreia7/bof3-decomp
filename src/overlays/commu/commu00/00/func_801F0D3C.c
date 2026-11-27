#include "commu00_00.h"

/* Byte fields of each 8-byte record-type entry. */
#define RECORD_TYPE_FIELD_2(index) (D_801457AA[((index) & BYTE_MASK) * 8])

MATCH void func_801F0D3C(u8 task_index, u8 record_type_index) {
    u32 key_term;
    u32 field_term;

    if (D_801F2928[record_type_index & BYTE_MASK] != 0) {
        SELF(Actor)->unk_06                     = 1;
        g_Actors[task_index & BYTE_MASK].unk_7C = (D_801F2928[record_type_index & BYTE_MASK] + 0xD1);
    } else {
        SELF(Actor)->unk_06                     = 5;
        g_Actors[task_index & BYTE_MASK].unk_7C = 0xC008;
        SELF(Actor)->unk_18                     = 0;
        key_term                                = (VILLAGE_ROOM_SUBTYPE(record_type_index) << 1);
        field_term                              = (RECORD_TYPE_FIELD_2(record_type_index) + 0x11);
        SELF(Actor)->unk_1C                     = key_term + field_term;
    }
}
