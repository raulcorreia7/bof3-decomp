#include "start_08.h"

MATCH s32 func_801E8C9C(u8 save_slot, u8 record_kind, u8 record_value) {
    if (g_Items[record_kind].flags == 0) {
        return 2;
    }
    return D_801ED24C[g_SaveRecordTypeCommands[record_kind]](save_slot, record_value) & 0xFF;
}
