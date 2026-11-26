/* Spawns one field record for the character: claims a free g_SpawnedActors slot, writes the type byte at +0x05, the caller's type at +0x01, the 16.16 position words at +0x34/+0x38, the ground height at +0x3E and clears the link byte at +0x0B. */
MATCH void PlChar_SpawnActor(u8 type, s32 x, s32 y) {
    u8 slot;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags     = 1;
        g_SpawnedActors[slot].type             = 0x34;
        g_SpawnedActors[slot].header.mode      = type;
        g_SpawnedActors[slot].pos.x.fixed      = x << 16;
        g_SpawnedActors[slot].pos.y.fixed      = y << 16;
        COORD_INT(g_SpawnedActors[slot].pos.z) = Area_HeightSample(g_SpawnedActors[slot].pos.x.fixed, g_SpawnedActors[slot].pos.y.fixed) + 0x100;
        g_SpawnedActors[slot].link             = 0;
    }
}
