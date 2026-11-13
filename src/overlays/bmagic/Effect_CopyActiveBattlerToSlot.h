/* Copies the 0x74 bytes of the active battler's work record into a queued effect slot: a party row below BATTLE_PARTY_CHARACTERS_COUNT, else an enemy row. */
/* func_801EFD4C (magic003), func_801EFAD4 (magic008) */

/* The 0x74 bytes of a battler row that a queued effect slot copies. */
typedef struct BattleWorkImage {
    u32 words[29];
} BattleWorkImage;

ASSERT_SIZE(BattleWorkImage, 0x74);

static inline void Effect_CopyActiveBattlerToSlot(u32 slot) {
    BattleWorkImage* dst;
    BattleWorkImage* src;
    u32              offset;
    u8               battler;

    battler = g_Battle.active_battler;
    if (battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        src  = (BattleWorkImage*)&g_Game.members[battler];
        dst  = (BattleWorkImage*)&g_BattleEffects[slot & BYTE_MASK];
        *dst = *src;
    } else {
        offset = (battler - BATTLE_PARTY_CHARACTERS_COUNT) * BATTLE_ENEMY_STRIDE;
        dst    = (BattleWorkImage*)&g_BattleEffects[slot & BYTE_MASK];
        *dst   = *(BattleWorkImage*)((u8*)g_BattleEnemyBattlers + offset);
    }
}
