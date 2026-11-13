#include "battle_15.h"

MATCH void func_800AC934(u8 entry_id) {
    u8* entry = (u8*)Battle_FindActorEntry(entry_id);
    entry[0]  = 0;
    entry[1]  = 0;
    entry[2]  = 0;
    entry[3]  = 0;
    entry[4]  = 0;
}
