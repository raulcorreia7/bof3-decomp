/* Raises the three tint bytes by 0x10; when the first byte, read as signed, reaches -0x40 it lowers the active battler's ticker and clears the effect. */
/* func_801EF688 (magic001), func_801F00A8 (magic001), func_801F0B8C (magic015) */
#define EFFECT_RAMP_TINT_AND_FINISH()             \
    SELF(PartyMember)->unk_5D += 0x10;            \
    SELF(PartyMember)->unk_5E += 0x10;            \
    SELF(PartyMember)->unk_5F += 0x10;            \
    if ((s8)SELF(PartyMember)->unk_5D == -0x40) { \
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;    \
        Effect_Reset();                           \
    }
