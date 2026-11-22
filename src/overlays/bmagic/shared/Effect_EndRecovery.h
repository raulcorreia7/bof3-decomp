/* Finishes the effect on its targets. */
MATCH void Effect_EndRecovery(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Battle_MarkDamaged(TASK(PartyMember)->unk_04);
        Effect_Reset();
    }
}
