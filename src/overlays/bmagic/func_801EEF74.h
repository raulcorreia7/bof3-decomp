/* Dispatches the effect step byte and, while the effect is active, draws it with the actor matrix.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEF74 (magic055), func_801EEF74 (magic091) */
MATCH void func_801EEF74(void) {
    SYS_DISPATCH_BYTE(D_801EFC64, g_SpadWork->step_01);
    if (g_SpadWork->flags_00 != 0 && g_SpadWork->step_01 != 0) {
        Effect_SetActorMatrix();
        func_801EF240();
        PopMatrix();
    }
}
