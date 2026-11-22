/* Updates the linked actor facing after the timer expires. Check every including image after changes. */
MATCH void PlChar_UpdateLinkedFacing(void) {
    u8 timer;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Request(TASK(Actor)->direction);
        TASK(Actor)->unk_03 = 2;
        return;
    }
    timer = TASK(Actor)->unk_0A;
    if (timer != 0) {
        TASK(Actor)->unk_0A = timer - 1;
        if (TASK(Actor)->unk_0A == 0) {
            g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_08 = TASK(Actor)->direction;
            if (TASK(Actor)->option_flags == 0) {
                TASK(Actor)->option_flags = ACTOR_OPT_HIDDEN_ON_SPAWN;
            }
            g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_0A = TASK(Actor)->option_flags;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
        }
    }
}
