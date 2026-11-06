#include "start_08.h"

MATCH s32 func_801E8C9C(u8 save_slot, u8 record_kind, u8 record_value) {
    if (D_801C8970[record_kind * 0x12] == 0) {
        return 2;
    }
    return D_801ED24C[g_SaveRecordTypeCommands[record_kind]](save_slot, record_value) & BYTE_MASK;
}
