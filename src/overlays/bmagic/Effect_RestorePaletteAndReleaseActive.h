/* When the effect ticker runs down: restores the arena palette from the bank
 * at 0x80033C00 (func_800AFC54), advances the active battler's script step
 * (func_800AEF98), clears the battler's flag bit 0x40 and steps the handler.
 * One body shared by the members below; every change must verify every member.
 */
/* func_801EF6AC (magic008), func_801EF150 (magic015), func_801EF594 (magic015) */
#define EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE() \
    if (g_SpadWork->word_08.byte.unk_0B == 0) {     \
        func_800AFC54();                            \
        func_800AEF98(4, 0);                        \
        BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;       \
        g_SpadWork->step_01 += 1;                   \
    }
