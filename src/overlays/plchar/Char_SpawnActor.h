/* Spawns one field record for the character: claims a free g_ActorSlots slot,
 * writes the kind byte at +0x05, the caller's kind at +0x01, the 16.16
 * position words at +0x34/+0x38, the ground height at +0x3E and clears
 * the link byte at +0x0B. One definition shared by the plchar character
 * programs; every change here must verify every member image. */
MATCH void Char_SpawnActor(s32 arg0, s32 arg1, s32 arg2) {
    /* FAKE: retail keeps the kind in $s1 and the position words in $s2/$s3;
     * gcc-2.7.2 assigns the first two registers by live length instead. */
    MATCH_REG(s32, y, "s3");
    MATCH_REG(s32, kind, "s1");
    s32 x;
    u8  slot;
    s32 x_word;
    s32 y_word;

    x    = arg1;
    y    = arg2;
    kind = arg0;
    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].flags_00       = 1;
        g_ActorSlots[slot].type           = 0x34;
        x_word                            = x << 16;
        g_ActorSlots[slot].x.fixed        = x_word;
        y_word                            = y << 16;
        g_ActorSlots[slot].unk_01         = kind;
        g_ActorSlots[slot].y.fixed        = y_word;
        g_ActorSlots[slot].z.part.integer = Area_SampleHeight(g_ActorSlots[slot].x.fixed, y_word) + 0x100;
        g_ActorSlots[slot].link_0B        = 0;
    }
}
