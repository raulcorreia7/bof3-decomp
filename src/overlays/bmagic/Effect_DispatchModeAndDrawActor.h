/* Dispatch the effect step by header.mode, then while the effect is flagged
 * move the actor's screen height and draw it, and release the effect. One
 * definition shared by the bmagic overlays that hold the three-entry table at
 * D_801EEC04; every change here must verify every member.
 */
/* func_801EEC10 (magic055, magic091) */
void func_801EF7B0(void);
void Effect_SetActorMatrix(void);
void func_801EF9E4(void);

MATCH void func_801EEC10(void) {
    BattleHandlerTable3 handlers = D_801EEC04;

    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.mode);
    if (g_Task->header.flags != 0) {
        func_800AF764();
        g_Task->unk_30.half -= 0x10;
        func_801EF7B0();
        Effect_SetActorMatrix();
        func_801EF9E4();
        PopMatrix();
    }
}
