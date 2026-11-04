#include "commu00_00.h"

/* room `subtype` (+1 of the 8-byte room rows based at g_FairyRooms). */

MATCH void func_801F0C6C(u8 task_index, u8 record_kind_index) {
    g_SpadWork->unk_06 = 1;

    if ((D_801455C4 == 7 && VILLAGE_ROOM_SUBTYPE(record_kind_index) != 0) ||
        (D_801455C3 == 0xA && VILLAGE_ROOM_SUBTYPE(record_kind_index) == 0)) {
        g_Actors[task_index].unk_7C = 0xCC;
    } else {
        g_Actors[task_index].unk_7C = VILLAGE_ROOM_SUBTYPE(record_kind_index) + 0xC8;
    }
}
