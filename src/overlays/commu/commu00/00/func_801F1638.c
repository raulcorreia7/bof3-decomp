#include "commu00_00.h"

MATCH void func_801F1638(void) {
    u8* record = FAIRY_VILLAGE_ACTIVE_UI;

    SELF_SET(record);
    record[8] = record[0x79];
    Script_DispatchSelector(SELF(Actor)->direction);
}
