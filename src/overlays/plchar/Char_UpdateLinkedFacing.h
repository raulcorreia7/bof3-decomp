/* Updates the linked actor facing after the timer expires. Check every including image after changes. */
MATCH void Char_UpdateLinkedFacing(void) {
    u8 timer;

    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->unk_03 = 2;
        return;
    }
    timer = g_Task->unk_0A;
    if (timer != 0) {
        g_Task->unk_0A = timer - 1;
        if (g_Task->unk_0A == 0) {
            g_SpawnedActors[g_Task->param.actor_slot].unk_08 = g_Task->direction_08;
            if (g_Task->option_flags == 0) {
                g_Task->option_flags = 1;
            }
            g_SpawnedActors[g_Task->param.actor_slot].unk_0A = g_Task->option_flags;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 11));
        }
    }
}
