/* Runs one route step's script with this image's turn facings; the body is CHAR_RUN_STEP_SCRIPT in plchar.h. */
MATCH void Char_RunStepScript(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}
