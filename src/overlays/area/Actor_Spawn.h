/* Spawns an actor record of kind 0x44. */
/* func_801F2E1C (area078), func_801F3D50 (area080) */
MATCH void Actor_Spawn(void) {
    s32        slot;
    SpawnedActor* row;

    slot = Actor_FindFreeSlot() & BYTE_MASK;
    if (slot != GAME_NONE) {
        row               = &g_SpawnedActors[slot];
        row->header.flags = 1;
        row->type         = 0x44;
    }
}
