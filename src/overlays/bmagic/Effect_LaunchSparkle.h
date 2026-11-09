/* The launch offset row of the sparkle record being updated. */
#define EFFECT_SPARKLE_ROW_MASK 0x1F
#define EFFECT_SPARKLE_OFFSET() (EFFECT_SPARKLE_OFFSETS[EFFECT_SPARKLE_TASK->unk_07 & EFFECT_SPARKLE_ROW_MASK])

/* Waits out the launch delay of the current sparkle. */
/* Effect_LaunchSparkle (magic070, magic071, magic072, magic073, magic074, magic162, magic168). */
MATCH void Effect_LaunchSparkle(void) {
    PartyMember* battler;

    if (--EFFECT_SPARKLE_TASK->timer_05 == 0) {
        battler                     = g_BattleEffectBattler;
        EFFECT_SPARKLE_TASK->pos.x  = battler->pos.x;
        EFFECT_SPARKLE_TASK->pos.y  = battler->pos.y;
        EFFECT_SPARKLE_TASK->pos.z  = battler->pos.z;
        EFFECT_SPARKLE_TASK->unk_20 = battler->unk_2E.half;
        EFFECT_SPARKLE_TASK->unk_22 = battler->unk_30.half;
        if (EFFECT_SPARKLE_OFFSET().x < 0) {
            EFFECT_SPARKLE_TASK->unk_20 += EFFECT_SPARKLE_OFFSET().x - RANDOM_MASK(7);
        } else {
            EFFECT_SPARKLE_TASK->unk_20 += EFFECT_SPARKLE_OFFSET().x + RANDOM_MASK(7);
        }
        EFFECT_SPARKLE_TASK->unk_22 -= EFFECT_SPARKLE_OFFSET().y + RANDOM_MASK(7);
        /* FAKE: reread the work pointer after the y store. */
        FAKE_BARRIER();
        EFFECT_SPARKLE_TASK->unk_08   = EFFECT_SPARKLE_TASK->unk_20;
        EFFECT_SPARKLE_TASK->unk_0A   = RANDOM_MASK(1);
        EFFECT_SPARKLE_TASK->phase_0C = rand();
        EFFECT_SPARKLE_TASK->unk_07   = EFFECT_SPARKLE_RISE[EFFECT_SPARKLE_TASK->unk_04] + RANDOM_MASK(6);
        EFFECT_SPARKLE_TASK->timer_05 = 16;
        EFFECT_SPARKLE_TASK->unk_06   = 0;
        EFFECT_SPARKLE_TASK->header.step++;
    }
}
