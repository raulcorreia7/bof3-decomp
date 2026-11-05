#include "game_00.h"

MATCH void Actor_Free(u8 record_index) {
    g_ActorSlots[record_index].flags  = 0;
    g_ActorSlots[record_index].mode   = 0;
    g_ActorSlots[record_index].step   = 0;
    g_ActorSlots[record_index].unk_03 = 0;
    g_ActorSlots[record_index].unk_04 = 0;
}
