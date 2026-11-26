/* Turns the character and claims a type 0x1B spawned actor slot; verify every image after a change. */
MATCH void PlChar_StartSpawnedActorTurn(void) {
    u8 slot;

    if (!(SELF(Actor)->direction & 1)) {
        SELF(Actor)->direction = (SELF(Actor)->direction - 1) & 7;
    }
    slot                          = func_8019601C();
    SELF(Actor)->param.actor_slot = slot;
    if (SELF(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0x1B;
    }
    Script_Request((SELF(Actor)->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + 0x100);
    SELF(Actor)->header.step++;
}
