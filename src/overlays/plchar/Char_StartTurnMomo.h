/* Starts the walk route of Momo with its fixed turn facings. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void Char_StartTurnMomo(void) {
    CHAR_START_TURN(FACING_RIGHT, FACING_DOWN);
}
