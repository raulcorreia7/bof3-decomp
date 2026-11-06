#include "engine/slus/slus.h"

/* stores the value in the first empty slot of a byte table.
 */
MATCH s32 Char_AddAbility(s32 ability_id, s32 character_index, s32 to_stock, s32 mode) {
    u8* table;
    s32 limit;
    s32 index;
    s32 kind;

    kind = ability_id & 0xFF;
    if (kind == 0)
        return 0;
    if ((to_stock & 0xFF) == 0) {
        limit = 10;
        table = Char_GetAbilities(character_index, kind, mode);
    } else {
        limit = 128;
        table = D_8014546C;
    }
    index = 0;
    if ((limit & 0xFF) != 0) {
        do {
            if (*table == 0) {
                *table = ability_id;
                return 1;
            }
            table++;
            index++;
        } while ((index & 0xFF) < (u32)(limit & 0xFF));
    }
    return 0;
}
