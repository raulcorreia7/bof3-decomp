#ifndef CHAR_SPAWN_LINKED_ACTOR_H
#define CHAR_SPAWN_LINKED_ACTOR_H

/* Spawns one field record for the character and links it to actor slot 1: claims a free g_ActorSlots slot, writes the actor type at +0x05, the caller's kind at +0x01, the 16.16 position words at +0x34/+0x38 and the ground height plus 0x200 at +0x3E. */
static inline void Char_SpawnLinkedActor(s32 spawn_kind, s32 spawn_x, s32 spawn_y) {
    /* FAKE: retail keeps the spawn kind in $s2 and the y word in $s4;
     * gcc-2.7.2 assigns the kind and x the other way round. */
    FAKE_REG(s32, y, "s4");
    FAKE_REG(s32, kind, "s2");
    u8  slot;
    s32 x_word;
    s32 y_word;

    y    = spawn_y;
    kind = spawn_kind;
    slot = Actor_FindFreeSlot();
    if (slot != GAME_NONE) {
        g_ActorSlots[slot].header.flags     = 1;
        g_ActorSlots[slot].type             = 0x34;
        x_word                              = spawn_x << 16;
        g_ActorSlots[slot].pos.x.fixed      = x_word;
        y_word                              = y << 16;
        g_ActorSlots[slot].header.mode      = kind;
        g_ActorSlots[slot].pos.y.fixed      = y_word;
        COORD_INT(g_ActorSlots[slot].pos.z) = Area_SampleHeight(g_ActorSlots[slot].pos.x.fixed, y_word) + 0x200;
        g_ActorSlots[slot].link             = 1;
    }
}

#endif
