#include "engine/slus/slus.h"

/* stores the value in the first empty slot of a byte table.
 */
MATCH s32 Char_AddAbility(s32 ability_id, s32 character_index, s32 to_stock, s32 mode) {
    u8* table;
    s32 limit;
    s32 index;
    s32 kind;

    kind = ability_id & BYTE_MASK;
    if (kind == 0)
        return 0;
    if ((to_stock & BYTE_MASK) == 0) {
        limit = 10;
        table = Char_GetAbilities((u8)character_index, (u8)kind, (u8)mode);
    } else {
        limit = 128;
        table = D_8014546C;
    }
    index = 0;
    if ((u32)(limit & BYTE_MASK) != 0) {
        do {
            if (*table == 0) {
                *table = (u8)ability_id;
                return 1;
            }
            table++;
            index++;
        } while ((u32)(index & BYTE_MASK) < (u32)(limit & BYTE_MASK));
    }
    return 0;
}
