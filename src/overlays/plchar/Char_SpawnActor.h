/* Spawns one field record for the character. */
MATCH void Char_SpawnActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y) {
    /* FAKE: retail keeps the kind in $s1 and the position words in $s2/$s3;
     * gcc-2.7.2 assigns the first two registers by live length instead. */
    FAKE_REG(s32, y, "s3");
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
        g_ActorSlots[slot].header.flags     = 1;
        g_ActorSlots[slot].type             = 0x34;
        x_word                              = x << 16;
        g_ActorSlots[slot].pos.x.fixed      = x_word;
        y_word                              = y << 16;
        g_ActorSlots[slot].header.mode      = kind;
        g_ActorSlots[slot].pos.y.fixed      = y_word;
        COORD_INT(g_ActorSlots[slot].pos.z) = Area_SampleHeight(g_ActorSlots[slot].pos.x.fixed, y_word) + 0x100;
        g_ActorSlots[slot].link             = 0;
    }
}
