/* Counts the effect timer (work byte 0x09) down; at zero it copies the coordinates and height span of the g_BattleEffectBattler into the effect work, reloads the timer with 0x40, clears the effect counters (work bytes 0x0A, 0x0B) and advances the effect step (work byte 0x01). */
/* func_801EEFFC (magic055), func_801EEFFC (magic091) */
MATCH void Effect_FollowTarget(void) {
    u8           timer;
    PartyMember* src;
    PartyMember* work;

    timer               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 0) {
        src                       = BATTLE_ACTIVE_WORK;
        work                      = g_Task;
        work->pos.x               = src->pos.x;
        work->pos.y               = src->pos.y;
        work->pos.z               = src->pos.z;
        work->unk_09              = 0x40;
        BMAGIC_WORK->timer        = 0;
        BMAGIC_WORK->param.unk_0B = 0;
        BMAGIC_WORK->header.mode  = BMAGIC_WORK->header.mode + 1;
    }
}
