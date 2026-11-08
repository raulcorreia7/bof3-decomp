/* Runs the route step script of NinaAdult with its fixed turn facings. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void Char_RunStepScriptNinaAdult(void) {
    CHAR_RUN_STEP_SCRIPT(FACING_DOWN, FACING_RIGHT);
}
