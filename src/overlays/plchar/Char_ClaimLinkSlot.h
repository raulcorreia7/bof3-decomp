/* Launches the facing probe once the character's script reaches
 * CHAR_LAUNCH_SCRIPT_PC: claims a free actor slot for it, plays the cue, clears
 * the options and advances the task state. One definition shared by the plchar
 * character programs; every change here must verify every member. */
MATCH void Char_ClaimLinkSlot(void) {
    func_8014D978();
    if (g_SpadWork->script_pc == CHAR_LAUNCH_SCRIPT_PC) {
        g_SpadWork->unk_0B = Actor_FindFreeSlot();
        if (g_SpadWork->unk_0B != 0xFF) {
            g_ActorSlots[g_SpadWork->unk_0B].flags_00 = 1;
            g_ActorSlots[g_SpadWork->unk_0B].type     = ACTOR_TYPE_FACING_PROBE;
        }
        /* FAKE: retail reads SND_PlayCue as void(s32). */
        ((void (*)(s32))SND_PlayCue)(g_SpadWork->unk_2C + 0x100);
        g_SpadWork->unk_07 = 0;
        g_SpadWork->state_02++;
    }
}
