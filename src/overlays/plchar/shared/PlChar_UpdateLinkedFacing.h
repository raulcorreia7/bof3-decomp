/* Updates the linked actor facing after the timer expires. Check every including image after changes. */
MATCH void PlChar_UpdateLinkedFacing(void) {
    u8 timer;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Request(SELF(Actor)->direction);
        SELF(Actor)->unk_03 = 2;
        return;
    }
    timer = SELF(Actor)->unk_0A;
    if (timer != 0) {
        SELF(Actor)->unk_0A = timer - 1;
        if (SELF(Actor)->unk_0A == 0) {
            g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_08 = SELF(Actor)->direction;
            if (SELF(Actor)->option_flags == 0) {
                SELF(Actor)->option_flags = ACTOR_OPT_HIDDEN_ON_SPAWN;
            }
            g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_0A = SELF(Actor)->option_flags;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 11));
        }
    }
}
