#include "battle_15.h"

/* func_800AC844 */
MATCH void Battle_ShowActorEntry(u8 entry_id) {
    u8* entry = (u8*)Battle_FindActorEntry(entry_id);
    *entry &= ~ACTOR_FLAG_HIDDEN;
}
