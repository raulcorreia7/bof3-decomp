/* When the effect ticker runs down: restores the arena palette from the bank at 0x80033C00 (func_800AFC54), advances the active battler's script step (Battle_SelectActiveBattlerScript), clears the battler's flag bit 0x40 and steps the handler. */
/* func_801EF6AC (magic008), func_801EF150 (magic015), func_801EF594 (magic015) */
#define EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE()                          \
    if (SELF(PartyMember)->param.unk_0B == 0) {                              \
        func_800AFC54();                                                     \
        Battle_SelectActiveBattlerScript(4, 0);                              \
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY; \
        SELF(PartyMember)->header.mode += 1;                                 \
    }
