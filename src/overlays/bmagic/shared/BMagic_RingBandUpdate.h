/* Runs the ring band step that header.mode selects from g_BMagicRingBandModes and, once past the first step, draws the band under the actor matrix. */
/* func_801EEF74 (magic055), func_801EEF74 (magic091) */
MATCH void BMagic_RingBandUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicRingBandModes, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.mode != 0) {
        Effect_SetActorMatrix();
        BMagic_RingBandDraw();
        PopMatrix();
    }
}
