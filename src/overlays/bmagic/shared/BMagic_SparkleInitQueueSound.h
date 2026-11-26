/* Task mode 0 as BMagic_SparkleInit, but it queues the selection sound before the sparkles spawn instead of playing it after. */
/* func_801EED38 (magic162), func_801EED38 (magic168) */
MATCH void BMagic_SparkleInitQueueSound(void) {
    PartyMember* battler;
    PartyMember* owner;
    u8           i;
    u8           sparkle_index;

    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        g_BMagicSparkles[i].header.flags = 0;
        g_BMagicSparkles[i].header.mode  = 0;
        g_BMagicSparkles[i].header.step  = 0;
    }
    SELF(PartyMember)->unk_04 = EFFECT_SPARKLE_TYPE;
    battler                   = g_Battle.selected_actor;
    SELF(PartyMember)->facing = battler->facing;
    SELF(PartyMember)->pos.x  = battler->pos.x;
    SELF(PartyMember)->pos.y  = battler->pos.y;
    SELF(PartyMember)->pos.z  = battler->pos.z;
    Battle_ProjectRange();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 8;
    SELF(PartyMember)->timer        = 0;
    SELF(PartyMember)->header.mode++;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));

    for (i = 0; i < g_BMagicSparkleCounts[SELF(PartyMember)->unk_04]; i++) {
        sparkle_index = BMagic_AllocEffect();
        if (sparkle_index != GAME_NONE) {
            owner                                       = SELF(PartyMember);
            g_BMagicSparkles[sparkle_index].header.mode = 0;
            g_BMagicSparkles[sparkle_index].header.step = 0;
            g_BMagicSparkles[sparkle_index].battler     = owner;
            g_BMagicSparkles[sparkle_index].unk_03      = RANDOM_MASK(3);
            g_BMagicSparkles[sparkle_index].unk_04      = SELF(PartyMember)->unk_04;
            g_BMagicSparkles[sparkle_index].unk_07      = i;
            g_BMagicSparkles[sparkle_index].timer_05    = g_BMagicSparkleDelays[SELF(PartyMember)->unk_04] * (i >> 2) + 1;
            SELF(PartyMember)->param.unk_0B++;
        }
    }
}
