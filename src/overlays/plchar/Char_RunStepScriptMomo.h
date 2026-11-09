/* Runs the route step script of Momo with its fixed turn facings. */
MATCH void Char_RunStepScriptMomo(void) {
    CHAR_RUN_STEP_CASES(FACING_DOWN, 0x41, FACING_RIGHT, 0x40);
}
