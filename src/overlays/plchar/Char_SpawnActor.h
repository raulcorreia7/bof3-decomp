/* Spawns one field record for the character: claims a free g_SpawnedActors slot, writes the kind byte at +0x05, the caller's kind at +0x01, the 16.16 position words at +0x34/+0x38, the ground height at +0x3E and clears the link byte at +0x0B. */
MATCH void Char_SpawnActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y) {
    /* FAKE: retail keeps the kind in $s1. */
    s32 y;
    FAKE_REG(s32, kind, "s1");
    s32 x;
    u8  slot;
    s32 x_word;
    s32 y_word;

    x    = spawn_x;
    y    = spawn_y;
    kind = spawn_kind;
    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags     = 1;
        g_SpawnedActors[slot].type             = 0x34;
        x_word                              = x << 16;
        g_SpawnedActors[slot].pos.x.fixed      = x_word;
        y_word                              = y << 16;
        g_SpawnedActors[slot].header.mode      = kind;
        g_SpawnedActors[slot].pos.y.fixed      = y_word;
        COORD_INT(g_SpawnedActors[slot].pos.z) = Area_SampleHeight(g_SpawnedActors[slot].pos.x.fixed, y_word) + 0x100;
        g_SpawnedActors[slot].link             = 0;
    }
}
