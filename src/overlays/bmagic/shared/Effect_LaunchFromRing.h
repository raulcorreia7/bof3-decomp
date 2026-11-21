/* Counts the effect down; at zero it places the effect on a ring of 22 units around its battler, at the angle in the
   work byte 0x0B, and launches it upward (rise 0x40, gravity -4, a 12-frame timer). Every change must verify every
   member. */
/* Effect_LaunchFromRing (magic062, magic082, magic083) */
MATCH void Effect_LaunchFromRing(void) {
    s16*         angle_cell;
    PartyMember* work;
    PartyMember* battler;
    u8           angle;
    s32          dy;

    if (--g_Task->unk_09 == 0) {
        angle_cell          = &D_1F800004;
        angle               = g_Task->param.unk_0B & 0x1F;
        *angle_cell         = angle << 7;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle << 7) * 0xB0) >> 3);
        dy                  = (rcos(*angle_cell) * 0xB0) >> 3;
        battler             = g_BattleEffectBattler;
        work                = g_Task;
        work->pos.y.fixed   = battler->pos.y.fixed + dy;
        work->pos.z.fixed   = battler->pos.z.fixed;
        work->unk_14        = 0x40;
        work->unk_20        = -4;
        work->unk_09        = 0;
        g_Task->timer       = 0xC;
        g_Task->unk_0C      = 1;
        g_Task->unk_10      = 0;
        g_Task->header.step += 1;
    }
}
