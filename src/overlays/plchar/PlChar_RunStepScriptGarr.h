/* Runs the route step script of Garr with its fixed turn facings. */
MATCH void PlChar_RunStepScriptGarr(void) {
    CHAR_RUN_STEP_SCRIPT(FACING_DOWN, FACING_RIGHT);
}
