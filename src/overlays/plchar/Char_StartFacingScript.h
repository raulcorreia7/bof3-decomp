/* Starts the character script named by the work record's cue byte once Actor_StepAnimOnce reports ready. */
MATCH void Char_StartFacingScript(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_SelectScript(g_Task->direction_08);
        g_Task->unk_03++;
    }
}
