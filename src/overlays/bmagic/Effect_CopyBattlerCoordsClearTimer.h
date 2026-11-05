/* Copies the coordinates and height span of the battler D_801EB4E0 into the effect work, clears the flag bit 0x40 of the work flags, clears the effect timer (work byte 0x09) and advances the effect step (work byte 0x02). One definition shared by the bmagic effect modules; every change here must verify every member. */
MATCH void Effect_CopyBattlerCoordsClearTimer(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    work              = g_Task;
    actor             = D_801EB4E0;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_09      = 0;
    work->pos.z.fixed = z;
    g_Task->step += 1;
}
