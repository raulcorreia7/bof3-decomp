/* Copies the coordinates and height span of the battler D_801EB4E0 into the effect work, clears the flag bit 0x40 of the work flags, sets the effect timer (work byte 0x09) and counter (work byte 0x0A) to one and advances the effect step (work byte 0x02). One definition shared by the bmagic effect modules; every change here must verify every member. */
MATCH void Effect_CopyBattlerCoordsSetTimers(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    work                 = g_Task;
    actor                = D_801EB4E0;
    work->coord_x_34.raw = actor->coord_x_34.raw;
    work->coord_y_38.raw = actor->coord_y_38.raw;
    z                    = actor->word_3C.word;
    work->unk_09         = 1;
    work->word_3C.word   = z;
    g_Task->timer        = 1;
    g_Task->step += 1;
}
