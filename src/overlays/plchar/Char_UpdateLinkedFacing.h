/* Updates the linked actor facing after the timer expires. Check every including image after changes. */
MATCH void Char_UpdateLinkedFacing(void) {
    u8 timer;

    if (func_8014DAEC() & 0xFF) {
        Actor_RequestScript(g_SpadWork->direction_08);
        g_SpadWork->unk_03 = 2;
        return;
    }
    timer = g_SpadWork->unk_0A;
    if (timer != 0) {
        g_SpadWork->unk_0A = timer - 1;
        if (g_SpadWork->unk_0A == 0) {
            g_ActorSlots[g_SpadWork->unk_0B].unk_08 = g_SpadWork->direction_08;
            if (g_SpadWork->option_flags == 0) {
                g_SpadWork->option_flags = 1;
            }
            g_ActorSlots[g_SpadWork->unk_0B].unk_0A = g_SpadWork->option_flags;
            SND_PlayCue(0x10BU);
        }
    }
}
