/* Turns the character and claims a type 0x1B spawned actor slot; verify every image after a change. */
MATCH void PlChar_StartSpawnedActorTurn(void) {
    u8 slot;

    if (!(TASK(Actor)->direction & 1)) {
        TASK(Actor)->direction = (TASK(Actor)->direction - 1) & 7;
    }
    slot                          = func_8019601C();
    TASK(Actor)->param.actor_slot = slot;
    if (TASK(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 0x1B;
    }
    Script_Request((TASK(Actor)->direction >> 1) + 0x42);
    /* FAKE: retail reads SND_SEPlay as void(s32). */
    ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + 0x100);
    TASK(Actor)->header.step++;
}
