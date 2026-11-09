/* Runs one route step's script with this image's turn facings; the body is
 * CHAR_RUN_STEP_SCRIPT in plchar.h. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void Char_RunStepScript(void) {
    CHAR_RUN_STEP_SCRIPT(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}
