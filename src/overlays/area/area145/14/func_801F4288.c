#include "area145_14.h"

MATCH void func_801F4288(void) {
    u8* record;
    u8  i;

    record = Item_GetRecord(ITEM_CAT_VITAL, VITAL_ITEM_KEY);
    for (i = 0; i < 0xC; i++) {
        g_TextVariables[0][i] = record[i];
    }
    D_801490E4[0] = 0;
    Item_VitalAdd(VITAL_ITEM_KEY);
    Message_Request(2);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}
