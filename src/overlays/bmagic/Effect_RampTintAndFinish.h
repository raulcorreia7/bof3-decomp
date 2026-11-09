/* Raises the three tint bytes by 0x10. */
/* func_801EF688 (magic001), func_801F00A8 (magic001), func_801F0B8C (magic015) */
#define EFFECT_RAMP_TINT_AND_FINISH()          \
    g_Task->unk_5D += 0x10;                    \
    g_Task->unk_5E += 0x10;                    \
    g_Task->unk_5F += 0x10;                    \
    if ((s8)g_Task->unk_5D == -0x40) {         \
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1; \
        func_801E5988();                       \
    }
