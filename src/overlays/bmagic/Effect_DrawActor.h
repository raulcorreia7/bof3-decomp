/* Draws the effect's actor while the effect is flagged; the step handler for header.mode runs first. */
/* Effect_DrawActor (magic055, magic091) */
void func_801EF7B0(void);
void Effect_SetActorMatrix(void);
void func_801EF9E4(void);

MATCH void Effect_DrawActor(void) {
    ActorEffectSteps handlers = D_801EEC04;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);
    if (g_Task->header.flags != 0) {
        Battle_ProjectRange();
        g_Task->unk_30.half -= 0x10;
        func_801EF7B0();
        Effect_SetActorMatrix();
        func_801EF9E4();
        PopMatrix();
    }
}
