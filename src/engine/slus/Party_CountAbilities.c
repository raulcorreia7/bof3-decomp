#include "engine/slus/slus.h"

/* selects one ability panel by kind (or the shared default table), then counts its nonzero entries. */
MATCH u8 Party_CountAbilities(u8 character_index, u8 ability_type, u8 mode) {
    Character* record;
    u8*        table;
    u8         length;
    u8         count;
    u8         i;

    if (mode == 0) {
        record = &g_Characters[character_index];
    } else {
        record = &g_Game.members[character_index].chr;
    }
    switch (ability_type) {
        case ABILITY_TYPE_HEAL:
            table  = record->abilities.healing;
            length = 0xA;
            break;
        case ABILITY_TYPE_ASSIST:
            table  = record->abilities.assist;
            length = 0xA;
            break;
        case ABILITY_TYPE_ATTACK:
            table  = record->abilities.attack;
            length = 0xA;
            break;
        case ABILITY_TYPE_SKILL:
            table  = record->abilities.skill;
            length = 0xA;
            break;
        default:
            table  = D_8014546C;
            length = 0x80;
            break;
    }
    count = 0;
    for (i = 0; i < length; i++) {
        if (*table != 0) {
            count++;
        }
        table++;
    }
    return count;
}
