/* Sets the GTE rotation and translation like Effect_SetActorMatrix, with the
 * depth halved from the active battler's work record instead of the
 * scratchpad record. One definition shared by the bmagic effect modules; every
 * change here must verify every member. */
/* func_801EF728 (magic053), func_801EF664 (magic219), func_801EF938 (magic220), func_801EF75C (magic226) */
MATCH void Effect_SetActiveActorMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX_SPAN(BATTLE_ACTIVE_WORK);
}
