/* Clears the effect slots, copies the facing and position of the selected battler into the effect, queues the selection sound, and spawns the sparkles of EFFECT_SPARKLE_KIND, each group of four with a longer launch delay. Each image header defines EFFECT_SPARKLE_KIND and declares the kind tables D_801F0194 and D_801F019C. */
/* func_801EED38 (magic162), func_801EED38 (magic168) */
MATCH void func_801EED38(void) {
    PartyMember* battler;
    PartyMember* owner;
    u8           i;
    u8           sparkle_index;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
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
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));

    for (i = 0; i < D_801F0194[g_Task->unk_04]; i++) {
        sparkle_index = BMagic_AllocEffect();
        if (sparkle_index != GAME_NONE) {
            owner                                          = g_Task;
            BMAGIC_EFFECT_SLOTS[sparkle_index].header.mode = 0;
            BMAGIC_EFFECT_SLOTS[sparkle_index].header.step = 0;
            BMAGIC_EFFECT_SLOTS[sparkle_index].battler     = owner;
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_03      = RANDOM_MASK(3);
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_04      = g_Task->unk_04;
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_07      = i;
            BMAGIC_EFFECT_SLOTS[sparkle_index].timer_05    = D_801F019C[g_Task->unk_04] * (i >> 2) + 1;
            g_Task->param.unk_0B++;
        }
    }
}
