/* Ages and draws the spawn discs and frees the spent ones; returns whether any was active. Every change here must verify every member. */
/* func_801F5308 (area098), func_801F3E7C (area188), func_801F3984 (area172) */
MATCH s32 Area_StepSpawnSlots(void) {
    MATRIX         camera;
    AreaSpawnSlot* slot;
    s32            active;
    u8             i;
    u8             life;

    active = 0;
    Area_SetCameraMatrix(&camera);
    slot = MEM_PTR(AreaSpawnSlot, AREA_WORK);
    for (i = 0; i < AREA_SPAWN_SLOT_COUNT; i++) {
        if (slot->active != 0) {
            active = 1;
            life   = slot->life_02 - 1;
            slot->radius_14 -= AREA_SPAWN_SLOT_RADIUS_STEP;
            slot->life_02 = life;
            if (life == 0) {
                slot->active = 0;
            }
            Area_DrawSpawnSlot(slot);
        }
        slot++;
    }
    return active;
}
