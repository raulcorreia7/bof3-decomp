/* Clears the effect slots, copies the facing and position of the selected battler into the effect, queues the selection sound, and spawns the sparkles of EFFECT_SPARKLE_TYPE, each group of four with a longer launch delay. Each image header defines EFFECT_SPARKLE_TYPE and declares the type tables D_801F0194 and D_801F019C. */
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
    TASK(PartyMember)->unk_04 = EFFECT_SPARKLE_TYPE;
    battler                   = g_Battle.selected_actor;
    TASK(PartyMember)->facing = battler->facing;
    TASK(PartyMember)->pos.x  = battler->pos.x;
    TASK(PartyMember)->pos.y  = battler->pos.y;
    TASK(PartyMember)->pos.z  = battler->pos.z;
    Battle_ProjectRange();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 8;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode++;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));

    for (i = 0; i < D_801F0194[TASK(PartyMember)->unk_04]; i++) {
        sparkle_index = BMagic_AllocEffect();
        if (sparkle_index != GAME_NONE) {
            owner                                          = g_Task;
            BMAGIC_EFFECT_SLOTS[sparkle_index].header.mode = 0;
            BMAGIC_EFFECT_SLOTS[sparkle_index].header.step = 0;
            BMAGIC_EFFECT_SLOTS[sparkle_index].battler     = owner;
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_03      = RANDOM_MASK(3);
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_04      = TASK(PartyMember)->unk_04;
            BMAGIC_EFFECT_SLOTS[sparkle_index].unk_07      = i;
            BMAGIC_EFFECT_SLOTS[sparkle_index].timer_05    = D_801F019C[TASK(PartyMember)->unk_04] * (i >> 2) + 1;
            TASK(PartyMember)->param.unk_0B++;
        }
    }
}
