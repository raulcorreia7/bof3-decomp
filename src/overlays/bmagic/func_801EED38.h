/* Clears the sparkle pool, copies the facing and position of the selected battler into the effect, and spawns the sparkles of EFFECT_SPARKLE_KIND, each group of four with a longer launch delay. */
/* func_801EED38 (magic070), func_801EED38 (magic071), func_801EED38 (magic072) */
MATCH void func_801EED38(void) {
    PartyMember* battler;
    PartyMember* owner;
    u8           i;
    u8           sparkle_index;

    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        D_801F01B4[i].header.flags = 0;
        D_801F01B4[i].header.mode  = 0;
        D_801F01B4[i].header.step  = 0;
    }
    g_Task->unk_04 = EFFECT_SPARKLE_KIND;
    battler        = g_Battle.selected_actor;
    g_Task->facing = battler->facing;
    g_Task->pos.x  = battler->pos.x;
    g_Task->pos.y  = battler->pos.y;
    g_Task->pos.z  = battler->pos.z;
    Battle_ProjectRange();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 8;
    g_Task->timer        = 0;
    g_Task->header.mode++;

    for (i = 0; i < D_801F0198[g_Task->unk_04]; i++) {
        sparkle_index = func_801F0000();
        if (sparkle_index != GAME_NONE) {
            owner                                 = g_Task;
            D_801F01B4[sparkle_index].header.mode = 0;
            D_801F01B4[sparkle_index].header.step = 0;
            D_801F01B4[sparkle_index].battler     = owner;
            D_801F01B4[sparkle_index].unk_03      = RANDOM_MASK(3);
            D_801F01B4[sparkle_index].unk_04      = g_Task->unk_04;
            D_801F01B4[sparkle_index].unk_07      = i;
            D_801F01B4[sparkle_index].timer_05    = D_801F01A0[g_Task->unk_04] * (i >> 2) + 1;
            g_Task->param.unk_0B++;
        }
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
}
