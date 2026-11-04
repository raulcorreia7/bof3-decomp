/* Sets the actor matrix like Effect_SetActorMatrix, rolled by 512. Every change here must verify every member. */
/* func_801EF510 (magic097), func_801EF520 (magic098), func_801EF1B0 (magic099), func_801EF188 (magic143) */
MATCH void Effect_SetActorMatrixRolled(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 512;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}
