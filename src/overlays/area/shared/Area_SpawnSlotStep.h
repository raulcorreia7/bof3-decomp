/* Counts the spawn counter (0x06) up, claims a spawn slot on every fourth count, calls DRAW, updates the slots, sets the timer to 32 and advances the mode. */
/* AREA_SPAWN_SLOT_STEP (area098 0x801F3B5C, area188 0x801F364C) */
#define AREA_SPAWN_SLOT_STEP(DRAW)             \
    u8 count;                                  \
    count               = TASK(Actor)->unk_06; \
    TASK(Actor)->unk_06 = count + 1;           \
    if ((count & 3) == 0) {                    \
        Area_ClaimSpawnSlot();                 \
    }                                          \
    DRAW();                                    \
    Area_UpdateSpawnSlots();                   \
    TASK(Actor)->timer = 32;                   \
    TASK(Actor)->header.mode += 1;
