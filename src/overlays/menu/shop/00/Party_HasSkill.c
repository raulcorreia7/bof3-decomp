#include "shop_00.h"

/* File-local declarations: the two shop item-id tables are owned by the
 * executable overlay; this function searches them read-only. */

MATCH bool Party_HasSkill(s32 item_id) {
    u8* abilities;
    u8  i;
    u8  j;

    for (j = 0; j < CHAR_INDEX_WHELP; j++) {
        abilities = g_Characters[0].abilities.skill + j * sizeof(Character);
        for (i = 0; i < CHARACTER_ABILITY_COUNT; i++) {
            if (*abilities == (item_id & BYTE_MASK)) {
                return 1;
            }
            abilities++;
        }
    }
    abilities = D_8014546C;
    for (i = 0; i < ABILITY_STOCK_SLOT_COUNT; i++) {
        if (*abilities == (item_id & BYTE_MASK)) {
            return 1;
        }
        abilities++;
    }
    return 0;
}
