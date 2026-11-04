#include "shop_00.h"

/* File-local declarations: the two shop item-id tables are owned by the
 * executable overlay; this function searches them read-only. */

MATCH s32 Party_HasSkill(s32 item_id) {
    u8* row;
    u8  i;
    u8  j;

    for (j = 0; j < 7; j++) {
        row = g_Characters[j].skill_abilities;
        for (i = 0; i < 10; i++) {
            if (*row == (item_id & BYTE_MASK)) {
                return 1;
            }
            row++;
        }
    }
    row = D_8014546C;
    for (i = 0; i < 128; i++) {
        if (*row == (item_id & BYTE_MASK)) {
            return 1;
        }
        row++;
    }
    return 0;
}
