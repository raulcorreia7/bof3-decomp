#include "start_08.h"

MATCH s32 func_801E8270(s32 character_index, s32 record_index) {
    Character* rec;

    if ((record_index & 0xFF) == 0) {
        rec = &g_Characters[character_index & 0xFF];
    } else {
        rec = (Character*)(D_80145F04 + (character_index & 0xFF) * BATTLE_PARTY_STRIDE);
    }
    rec->hp = 1;
    return -((Char_ClearStatus(character_index & 0xFF, 0x4000, record_index & 0xFF) & 0xFF) == 0) & 3;
}
