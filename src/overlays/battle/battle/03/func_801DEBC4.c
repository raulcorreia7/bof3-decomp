#include "battle_03.h"

MATCH void func_801DEBC4(u32 script_index, u32 event_index) {
    u16 event_id;

    event_id = D_801EB09C[script_index & BYTE_MASK][event_index & BYTE_MASK];
    func_801DE560(2u, 0u, 0u, 45u, Message_GetText(event_id));
}
