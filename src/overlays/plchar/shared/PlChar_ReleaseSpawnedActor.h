/* Counts the character's spawn down and releases its actor slot; every change must verify every plchar image that includes it. */
MATCH void PlChar_ReleaseSpawnedActor(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Request(SELF(Actor)->direction);
        SELF(Actor)->unk_03 = FACING_UP_RIGHT;
        return;
    }
    if (SELF(Actor)->unk_0A != 0) {
        SELF(Actor)->unk_0A--;
        if (SELF(Actor)->unk_0A == 0) {
            /* FAKE: retail reads SND_SEPlay as void(s32). */
            ((void (*)(s32))SND_SEPlay)(SELF(Actor)->unk_2C + EMI_SE_ID(SND_BANK_COMMON, 0));
            g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_08 = SELF(Actor)->direction;
            if (SELF(Actor)->option_flags == 0) {
                SELF(Actor)->option_flags = ACTOR_OPT_HIDDEN_ON_SPAWN;
            }
            g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_0A = SELF(Actor)->option_flags;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
        }
    }
}
