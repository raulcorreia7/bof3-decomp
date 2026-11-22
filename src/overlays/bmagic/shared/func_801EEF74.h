/* Dispatches the effect step byte and, while the effect is active, draws it with the actor matrix. */
/* func_801EEF74 (magic055), func_801EEF74 (magic091) */
MATCH void func_801EEF74(void) {
    SYS_DISPATCH_BYTE(D_801EFC64, BMAGIC_WORK->header.mode);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.mode != 0) {
        Effect_SetActorMatrix();
        func_801EF240();
        PopMatrix();
    }
}
