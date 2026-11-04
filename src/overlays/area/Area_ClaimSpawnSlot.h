/* Claims the first free slot of the spawn table: sets it active and starts it
 * at the actor position with the image's AREA_SPAWN_SLOT_LIFE,
 * AREA_SPAWN_SLOT_RADIUS and AREA_SPAWN_SLOT_CORE_SHADE. One definition shared
 * by the world area overlays; every change here must verify every member. */
/* func_801F526C (area098), func_801F3DE0 (area188), func_801F38E8 (area172) */
MATCH void Area_ClaimSpawnSlot(void) {
    AreaSpawnSlot* slot;
    u8             i;

    slot = MEM_PTR(AreaSpawnSlot, AREA_WORK_WINDOW_ADDRESS);
    for (i = 0; i < AREA_SPAWN_SLOT_COUNT; i++) {
        if (slot->active == 0) {
            slot->active        = 1;
            slot->unk_01        = 0;
            slot->life_02       = AREA_SPAWN_SLOT_LIFE;
            slot->x             = g_SpadWork->x;
            slot->y             = g_SpadWork->y;
            slot->z             = g_SpadWork->z;
            slot->radius_14     = AREA_SPAWN_SLOT_RADIUS;
            slot->core_shade_16 = AREA_SPAWN_SLOT_CORE_SHADE;
            slot->rim_shade_17  = 0;
            return;
        }
        slot++;
    }
}
