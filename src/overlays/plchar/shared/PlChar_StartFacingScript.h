/* Starts the character script named by the work record's cue byte once Script_AnimStepOnce reports ready, then advances the work byte at +0x03. */
MATCH void PlChar_StartFacingScript(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Script_Select(g_Task->direction);
        g_Task->unk_03++;
    }
}
