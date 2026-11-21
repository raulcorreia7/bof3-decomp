/* Sets the actor matrix like Effect_SetActorMatrix, rolled a quarter turn when the effect flag is set. */
/* func_801EFA18 (magic107), func_801F1408 (magic151) */
MATCH void Effect_SetActorMatrixQuarterRoll(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (g_Task->facing & 1) {
        rot.vz = ONE / 4;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}
