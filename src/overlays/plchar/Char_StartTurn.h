/* Starts the character's walk route with this image's turn facings; the body is
 * CHAR_START_TURN in plchar.h. One definition shared by the plchar character
 * programs; every change here must verify every member image. */
MATCH void Char_StartTurn(void) {
    CHAR_START_TURN(CHARACTER_FACING_BACK, CHARACTER_FACING_AWAY);
}
