/* Starts the character script named by the work record's cue byte once Actor_StepAnimOnce reports ready, then advances the work byte at +0x03. */
MATCH void PlChar_StartFacingScript(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_SelectScript(g_Task->direction);
        g_Task->unk_03++;
    }
}
