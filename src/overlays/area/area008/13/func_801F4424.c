#include "area008_13.h"

/* Retail passes no mode argument (the etc/game/00 revision ignores it), so the
 * callee is declared arg-less. */

/* Entry table at 0x80143FC8 with its byte-field views: flag at `+0x00`, kind at
 * `+0x05`, derived byte at `+0x0B`, stride 0x74. */

/* Scratchpad byte cell that holds the staged slot index; the shipped code takes
 * its symbol address. */

/* Work-record pointer cell immediately before the record array g_Actors:
 * its byte distance past the array base, divided by the record stride, is the
 * slot index of the record it selects, which this function files at the
 * entry's `+0x0B` byte. */

MATCH void func_801F4424(void) {
    u8 slot_index;

    slot_index    = Actor_FindFreeSlot();
    D_1F800000[0] = slot_index;
    if (slot_index == GAME_NONE) {
        return;
    }
    g_ActorSlots[(u32)slot_index].flags   = 1;
    g_ActorSlots[(u32)D_1F800000[0]].type = 0x54;
    g_ActorSlots[(u32)D_1F800000[0]].link = (s8)((s32)(-((g_CurrentActor - (s32)g_Actors) * 0xD79435E5)) >> 3);
}
