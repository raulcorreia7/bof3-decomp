/* The module entry: runs the task step that header.mode selects from g_BMagicRingModes, then draws the disc, the actor matrix and the shade behind the battlers. */
/* func_801EEC10 (magic055), func_801EEC10 (magic091) */

MATCH void Effect_DrawActor(void) {
    BMagicActorSteps handlers = g_BMagicRingModes;

    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->header.flags != 0) {
        Battle_ProjectRange();
        TASK(PartyMember)->screen_y.value -= 0x10;
        BMagic_RingDrawDisc();
        Effect_SetActorMatrix();
        BMagic_RingDrawShade();
        PopMatrix();
    }
}
