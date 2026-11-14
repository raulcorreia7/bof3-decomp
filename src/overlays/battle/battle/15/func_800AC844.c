#include "battle_15.h"

MATCH void func_800AC844(u8 entry_id) {
    u8* entry = (u8*)Battle_FindActorEntry(entry_id);
    *entry &= 0xBF;
}
