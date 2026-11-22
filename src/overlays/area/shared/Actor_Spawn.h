/* Spawns an actor record of type 0x44. */
/* func_801F2E1C (area078), func_801F3D50 (area080) */
MATCH void Actor_Spawn(void) {
    s32           slot;
    SpawnedActor* spawned_actor;

    slot = Actor_FindFreeSpawned() & BYTE_MASK;
    if (slot != GAME_NONE) {
        spawned_actor               = &g_SpawnedActors[slot];
        spawned_actor->header.flags = 1;
        spawned_actor->type         = 0x44;
    }
}
