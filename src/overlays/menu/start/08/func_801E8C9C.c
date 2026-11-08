#include "start_08.h"

MATCH s32 func_801E8C9C(u8 save_slot, u8 item_id, u8 record_value) {
    if (g_Items[item_id].flags == 0) {
        return 2;
    }
    return D_801ED24C[g_SaveRecordTypeCommands[item_id]](save_slot, record_value) & BYTE_MASK;
}
