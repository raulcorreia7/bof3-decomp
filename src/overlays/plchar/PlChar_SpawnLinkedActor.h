/* Spawns and links a field actor; verify changes in plp016, plp026, plp034, plp056, plp267, plp349, plp467, plp567 and plp678. */
MATCH void PlChar_SpawnLinkedActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y, s32 cell_code) {
    /* FAKE: plain C was 0xE4; retail keeps x in s3. */
    FAKE_REG(s32, x, "s3");
    /* FAKE: plain C was 0xE4; retail keeps y in s4. */
    FAKE_REG(s32, y, "s4");
    /* FAKE: plain C was 0xE4; retail keeps kind in s2. */
    FAKE_REG(s32, kind, "s2");
    /* FAKE: plain C was 0xE4; retail keeps one in s1. */
    FAKE_REG(s32, one, "s1");
    /* FAKE: plain C was 0xE4; retail shifts x into v0. */
    FAKE_REG(s32, x_word, "v0");
    u8  slot;
    s32 y_word;

    x    = spawn_x;
    y    = spawn_y;
    kind = spawn_kind;
    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        /* FAKE: plain C was 0xE4; retail computes the slot stride first. */
        FAKE_ORDER_LOCK(FAKE_USE(slot * sizeof(SpawnedActor)));
        /* FAKE: plain C was 0xE4; retail loads one before the type. */
        FAKE_ORDER_LOCK(one = 1);
        /* FAKE: plain C was 0xE4; the type store follows the flag load. */
        FAKE_ORDER_LOCK(g_SpawnedActors[slot].type = 0x34);
        x_word = x << 16;
        /* FAKE: plain C was 0xE4; retail shifts x into v0 before the store. */
        FAKE_USE(x_word);
        g_SpawnedActors[slot].pos.x.fixed      = x_word;
        y_word                                 = y << 16;
        g_SpawnedActors[slot].header.flags     = one;
        g_SpawnedActors[slot].header.mode      = kind;
        g_SpawnedActors[slot].pos.y.fixed      = y_word;
        COORD_INT(g_SpawnedActors[slot].pos.z) = Area_SampleHeight(g_SpawnedActors[slot].pos.x.fixed, y_word) + 0x200;
        g_SpawnedActors[slot].link             = one;
    }
}
