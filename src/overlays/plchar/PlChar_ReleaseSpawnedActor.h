/* Counts the character's spawn down and releases its actor slot; every change must verify every plchar image that includes it. */
MATCH void PlChar_ReleaseSpawnedActor(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_RequestScript(g_Task->direction);
        g_Task->unk_03 = FACING_UP_RIGHT;
        return;
    }
    if (g_Task->unk_0A != 0) {
        g_Task->unk_0A--;
        if (g_Task->unk_0A == 0) {
            /* FAKE: retail reads SND_PlaySE as void(s32). */
            ((void (*)(s32))SND_PlaySE)(g_Task->unk_2C + EMI_CUE_ID(SND_BANK_COMMON, 0));
            g_SpawnedActors[g_Task->param.actor_slot].unk_08 = g_Task->direction;
            if (g_Task->option_flags == 0) {
                g_Task->option_flags = ACTOR_OPT_HIDDEN_ON_SPAWN;
            }
            g_SpawnedActors[g_Task->param.actor_slot].unk_0A = g_Task->option_flags;
            SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 11));
        }
    }
}
