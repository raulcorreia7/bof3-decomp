/* Waits for the work counter at +0x58 to reach 10, then claims a free actor
 * slot as the linked one (work byte +0x0B, type 0x3A), plays the walk cue,
 * clears the option byte and advances the task state. One definition shared by
 * the plchar character programs; each program includes it where the function
 * sits, and a change must keep every member matching. */
MATCH void Char_ClaimLinkSlot(void) {
    func_8014D978();
    if (g_SpadWork->unk_58 == 10) {
        g_SpadWork->unk_0B = Actor_FindFreeSlot();
        if (g_SpadWork->unk_0B != 0xFF) {
            g_ActorSlots[g_SpadWork->unk_0B].flags_00 = 1;
            g_ActorSlots[g_SpadWork->unk_0B].type     = 0x3A;
        }
        /* FAKE: retail reads SND_PlayCue as void(s32). */
        ((void (*)(s32))SND_PlayCue)(g_SpadWork->unk_2C + 0x100);
        g_SpadWork->unk_07 = 0;
        g_SpadWork->state_02++;
    }
}
