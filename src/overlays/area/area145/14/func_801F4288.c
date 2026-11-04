#include "area145_14.h"

MATCH void func_801F4288(void) {
    u8* record;
    u8  i;

    record = Item_GetRecord(4, 0xB);
    for (i = 0; i < 0xC; i++) {
        g_TextVariables[0][i] = record[i];
    }
    D_801490E4 = 0;
    Party_AddVitalItem(0xB);
    Resource_RequestArea(2);
    g_GameStateIndex = 2;
}
