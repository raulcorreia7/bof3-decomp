#include "battle_03.h"

/* func_801DEA64 */
MATCH void Battle_ShowMessage(s32 message_slot) {
    void* table;

    table = &D_801492B8;
    SYS_CopyString(table, (u8*)(message_slot + 0x74), 5u);
    if (D_801463BA != 0u) {
        strcat((char*)table, (char*)D_801EB00D);
    }
    func_801DE60C(0u, 1u, 1u, 0u, 255u, table);
}
