/* Spawns and links a field actor; verify changes in plp016, plp026, plp034, plp056, plp267, plp349, plp467, plp567 and plp678. */
MATCH void PlChar_SpawnLinkedActor(u8 type, s32 x, s32 y, s32 cell_code) {
    u8 slot;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags     = 1;
        g_SpawnedActors[slot].type             = 0x34;
        g_SpawnedActors[slot].header.mode      = type;
        g_SpawnedActors[slot].pos.x.fixed      = x << 16;
        g_SpawnedActors[slot].pos.y.fixed      = y << 16;
        COORD_INT(g_SpawnedActors[slot].pos.z) = Area_HeightSample(g_SpawnedActors[slot].pos.x.fixed, g_SpawnedActors[slot].pos.y.fixed) + 0x200;
        g_SpawnedActors[slot].link             = 1;
    }
}
