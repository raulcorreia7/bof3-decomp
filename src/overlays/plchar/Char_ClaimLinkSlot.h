/* Launches the facing probe from a free actor slot once the script reaches CHAR_LAUNCH_SCRIPT_PC. Every change here must verify every member. */
MATCH void Char_ClaimLinkSlot(void) {
    func_8014D978();
    if (g_Task->script_pc == CHAR_LAUNCH_SCRIPT_PC) {
        g_Task->unk_0B = Actor_FindFreeSlot();
        if (g_Task->unk_0B != 0xFF) {
            g_ActorSlots[g_Task->unk_0B].header.flags = 1;
            g_ActorSlots[g_Task->unk_0B].type         = ACTOR_TYPE_FACING_PROBE;
        }
        /* FAKE: retail reads SND_PlayCue as void(s32). */
        ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
        g_Task->option_flags = 0;
        g_Task->header.step++;
    }
}
