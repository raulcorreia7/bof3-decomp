/* Counts the effect timer (work byte 0x09) down; at zero it copies the coordinates
 * and height span of the g_BattleEffectBattler into the effect work, reloads the
 * timer with 0x40, clears the effect counters (work bytes 0x0A, 0x0B) and advances
 * the effect step (work byte 0x01). One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEFFC (magic055), func_801EEFFC (magic091) */
MATCH void Effect_FollowTarget(void) {
    u8           timer;
    PartyMember* src;
    PartyMember* work;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        src                  = BATTLE_ACTIVE_WORK;
        work                 = g_Task;
        work->pos.x          = src->pos.x;
        work->pos.y          = src->pos.y;
        work->pos.z          = src->pos.z;
        work->unk_09         = 0x40;
        g_Task->timer        = 0;
        g_Task->param.unk_0B = 0;
        g_Task->header.mode  = g_Task->header.mode + 1;
    }
}
