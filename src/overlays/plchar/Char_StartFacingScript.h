/* Starts the character script named by the work record's cue byte once
 * Actor_StepAnimOnce reports ready, then advances the work byte at +0x03. One
 * definition shared by the plchar character programs; each program includes
 * it where the function sits, and a change must keep every member matching.
 */
MATCH void Char_StartFacingScript(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Actor_SelectScript(g_Task->direction_08);
        g_Task->unk_03++;
    }
}
