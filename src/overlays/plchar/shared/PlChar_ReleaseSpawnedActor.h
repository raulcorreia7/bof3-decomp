/* Counts the character's spawn down and releases its actor slot; every change must verify every plchar image that includes it. */
MATCH void PlChar_ReleaseSpawnedActor(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Request(TASK(Actor)->direction);
        TASK(Actor)->unk_03 = FACING_UP_RIGHT;
        return;
    }
    if (TASK(Actor)->unk_0A != 0) {
        TASK(Actor)->unk_0A--;
        if (TASK(Actor)->unk_0A == 0) {
            /* FAKE: retail reads SND_SEPlay as void(s32). */
            ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + EMI_SE_ID(SND_BANK_COMMON, 0));
            g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_08 = TASK(Actor)->direction;
            if (TASK(Actor)->option_flags == 0) {
                TASK(Actor)->option_flags = ACTOR_OPT_HIDDEN_ON_SPAWN;
            }
            g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_0A = TASK(Actor)->option_flags;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
        }
    }
}
