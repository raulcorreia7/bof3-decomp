/* Starts the walk route of Garr with its fixed turn facings. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void Char_StartTurnGarr(void) {
    CHAR_START_TURN(FACING_RIGHT, FACING_DOWN);
}
