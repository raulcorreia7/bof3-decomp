#include "commu00_00.h"

/* The work cell is stored through SP_REF and re-read through the file-local
 * cell symbol, so each access emits its own address load. */
MATCH void func_801F1638(void) {
    u8* record = FAIRY_VILLAGE_ACTIVE_UI;

    SP_REF(u8*, 0x44u) = record;
    record[8]          = record[0x79];
    func_8015BAC4(g_Task->direction_08);
}
