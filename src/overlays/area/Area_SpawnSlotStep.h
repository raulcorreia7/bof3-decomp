/* Counts the spawn counter (0x06) up, claims a spawn slot on every fourth count, calls DRAW, updates the slots, sets
 * the timer to 32 and advances the mode. A statement macro shared by the area overlays; every change here must verify every member. */
/* AREA_SPAWN_SLOT_STEP (area098 0x801F3B5C, area188 0x801F364C) */
#define AREA_SPAWN_SLOT_STEP(DRAW)   \
    u8 count;                        \
    count          = g_Task->unk_06; \
    g_Task->unk_06 = count + 1;      \
    if ((count & 3) == 0) {          \
        Area_ClaimSpawnSlot();       \
    }                                \
    DRAW();                          \
    Area_UpdateSpawnSlots();         \
    g_Task->timer = 32;              \
    g_Task->header.mode += 1;
