/* Copies the coordinates and height span of the g_BattleEffectBattler into the effect work, clears the flag bit 0x40 of the work flags, sets the effect timer (work byte 0x09) and counter (work byte 0x0A) to one and advances the effect step (work byte 0x02). */
MATCH void Effect_StartAtTarget(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    work                     = SELF(PartyMember);
    actor                    = g_BattleEffectBattler;
    work->pos.x.fixed        = actor->pos.x.fixed;
    work->pos.y.fixed        = actor->pos.y.fixed;
    z                        = actor->pos.z.fixed;
    work->unk_09             = 1;
    work->pos.z.fixed        = z;
    SELF(PartyMember)->timer = 1;
    SELF(PartyMember)->header.step += 1;
}
