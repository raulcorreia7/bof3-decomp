/* Dispatches the effect step byte and, while the effect is active, draws it with the actor matrix. */
/* func_801EEF74 (magic055), func_801EEF74 (magic091) */
MATCH void func_801EEF74(void) {
    SYS_DISPATCH_BYTE(D_801EFC64, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.mode != 0) {
        Effect_SetActorMatrix();
        func_801EF240();
        PopMatrix();
    }
}
