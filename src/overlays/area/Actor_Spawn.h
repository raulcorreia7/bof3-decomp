/* Spawns an actor record of kind 0x44. One definition shared by the two world
 * area overlays; every change here must verify every member. */
/* func_801F2E1C (area078), func_801F3D50 (area080) */
MATCH void Actor_Spawn(void) {
    s32        slot;
    ActorSlot* row;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        row        = &g_ActorSlots[slot];
        row->flags = 1;
        row->type  = 0x44;
    }
}
