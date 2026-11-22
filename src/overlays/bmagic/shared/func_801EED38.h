/* Clears the sparkle pool, copies the facing and position of the selected battler into the effect, and spawns the sparkles of EFFECT_SPARKLE_TYPE, each group of four with a longer launch delay. */
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

    for (i = 0; i < D_801F0198[TASK(PartyMember)->unk_04]; i++) {
        sparkle_index = func_801F0000();
        if (sparkle_index != GAME_NONE) {
            owner                                 = TASK(PartyMember);
            D_801F01B4[sparkle_index].header.mode = 0;
            D_801F01B4[sparkle_index].header.step = 0;
            D_801F01B4[sparkle_index].battler     = owner;
            D_801F01B4[sparkle_index].unk_03      = RANDOM_MASK(3);
            D_801F01B4[sparkle_index].unk_04      = TASK(PartyMember)->unk_04;
            D_801F01B4[sparkle_index].unk_07      = i;
            D_801F01B4[sparkle_index].timer_05    = D_801F01A0[TASK(PartyMember)->unk_04] * (i >> 2) + 1;
            TASK(PartyMember)->param.unk_0B++;
        }
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
}
