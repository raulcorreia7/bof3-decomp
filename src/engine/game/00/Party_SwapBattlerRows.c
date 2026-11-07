#include "game_00.h"

/* nonmatching unmeasured: tried volatile FIELD(T,&sym,off) byte-offset swaps (63.25%); retail order is load A, load B /
 * load B, load A, store A, store B per pair with off_a=a0 and off_b=v1 kept in the arg regs; mine copies the offsets
 * (move t0,a0) and orders loads differently. */
#ifdef NON_MATCHING
NON_MATCHING void Party_SwapBattlerRows(s32 slot_a, s32 slot_b, s32 skip_state) {
    s32 off_a;
    s32 off_b;
    u8  val_b;
    s32 val_w;

    off_a = (slot_a & BYTE_MASK) * BATTLE_PARTY_STRIDE;
    off_b = (slot_b & BYTE_MASK) * BATTLE_PARTY_STRIDE;
    val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].chr.character_id, off_a);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].chr.character_id, off_a) =
        FIELD(volatile u8, &g_BattlePartyBattlers[0].chr.character_id, off_b);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].chr.character_id, off_b) = val_b;
    if (!(skip_state & BYTE_MASK)) {
        val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].facing, off_a);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].facing, off_a) =
            FIELD(volatile u8, &g_BattlePartyBattlers[0].facing, off_b);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].facing, off_b) = val_b;
        val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_29, off_a);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_29, off_a) =
            FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_29, off_b);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_29, off_b) = val_b;
        val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_12C[0], off_a);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_12C[0], off_a) =
            FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_12C[0], off_b);
        FIELD(volatile u8, &g_BattlePartyBattlers[0].unk_12C[0], off_b) = val_b;
        val_w                                                           = FIELD(volatile s32, &D_80145EC4, off_a);
        FIELD(volatile s32, &D_80145EC4, off_a)                         = FIELD(volatile s32, &D_80145EC4, off_b);
        FIELD(volatile s32, &D_80145EC4, off_b)                         = val_w;
        val_w                                                           = FIELD(volatile s32, &D_80145EC8, off_a);
        FIELD(volatile s32, &D_80145EC8, off_a)                         = FIELD(volatile s32, &D_80145EC8, off_b);
        FIELD(volatile s32, &D_80145EC8, off_b)                         = val_w;
        val_w                                                           = FIELD(volatile s32, &D_80145ECC, off_a);
        FIELD(volatile s32, &D_80145ECC, off_a)                         = FIELD(volatile s32, &D_80145ECC, off_b);
        FIELD(volatile s32, &D_80145ECC, off_b)                         = val_w;
    }
    val_w = FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_0C, off_a);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_0C, off_a) =
        FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_0C, off_b);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_0C, off_b) = val_w;
    val_w = FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_10, off_a);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_10, off_a) =
        FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_10, off_b);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_10, off_b) = val_w;
    val_w = FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_14, off_a);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_14, off_a) =
        FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_14, off_b);
    FIELD(volatile s32, &g_BattlePartyBattlers[0].unk_14, off_b) = val_w;
    val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.type, off_a);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.type, off_a) =
        FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.type, off_b);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.type, off_b) = val_b;
    val_b = FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.target, off_a);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.target, off_a) =
        FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.target, off_b);
    FIELD(volatile u8, &g_BattlePartyBattlers[0].turn.command.target, off_b) = val_b;
    FIELD(volatile u8, &D_80145EDB, off_a)                                   = 0xFF;
    FIELD(volatile u8, &D_80145EDB, off_b)                                   = 0xFF;
}
#else
INCLUDE_ASM(Party_SwapBattlerRows);
#endif
