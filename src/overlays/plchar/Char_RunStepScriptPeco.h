/* Runs the route step script of Peco with its fixed turn facings. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void Char_RunStepScriptPeco(void) {
    CHAR_RUN_STEP_SCRIPT(FACING_RIGHT, FACING_DOWN);
}
