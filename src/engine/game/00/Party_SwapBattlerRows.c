#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void Party_SwapBattlerRows(s32 slot_a, s32 slot_b, s32 skip_state) {
    s32 off_a;
    s32 off_b;
    u8  val_b;
    s32 val_w;

    off_a                                                          = (slot_a & BYTE_MASK) * BATTLE_PARTY_STRIDE;
    off_b                                                          = (slot_b & BYTE_MASK) * BATTLE_PARTY_STRIDE;
    val_b                                                          = FIELD(volatile u8, &g_Game.members[0].chr.character_id, off_a);
    FIELD(volatile u8, &g_Game.members[0].chr.character_id, off_a) = FIELD(volatile u8, &g_Game.members[0].chr.character_id, off_b);
    FIELD(volatile u8, &g_Game.members[0].chr.character_id, off_b) = val_b;
    if (!(skip_state & BYTE_MASK)) {
        val_b                                                                           = FIELD(volatile u8, &g_Game.members[0].facing, off_a);
        FIELD(volatile u8, &g_Game.members[0].facing, off_a)                            = FIELD(volatile u8, &g_Game.members[0].facing, off_b);
        FIELD(volatile u8, &g_Game.members[0].facing, off_b)                            = val_b;
        val_b                                                                           = FIELD(volatile u8, &g_Game.members[0].unk_29, off_a);
        FIELD(volatile u8, &g_Game.members[0].unk_29, off_a)                            = FIELD(volatile u8, &g_Game.members[0].unk_29, off_b);
        FIELD(volatile u8, &g_Game.members[0].unk_29, off_b)                            = val_b;
        val_b                                                                           = FIELD(volatile u8, &g_Game.members[0].status.field.flags.unsigned_value, off_a);
        FIELD(volatile u8, &g_Game.members[0].status.field.flags.unsigned_value, off_a) = FIELD(volatile u8, &g_Game.members[0].status.field.flags.unsigned_value, off_b);
        FIELD(volatile u8, &g_Game.members[0].status.field.flags.unsigned_value, off_b) = val_b;
        val_w                                                                           = FIELD(volatile s32, &g_Game.members[0].pos.x.fixed, off_a);
        FIELD(volatile s32, &g_Game.members[0].pos.x.fixed, off_a)                      = FIELD(volatile s32, &g_Game.members[0].pos.x.fixed, off_b);
        FIELD(volatile s32, &g_Game.members[0].pos.x.fixed, off_b)                      = val_w;
        val_w                                                                           = FIELD(volatile s32, &g_Game.members[0].pos.y.fixed, off_a);
        FIELD(volatile s32, &g_Game.members[0].pos.y.fixed, off_a)                      = FIELD(volatile s32, &g_Game.members[0].pos.y.fixed, off_b);
        FIELD(volatile s32, &g_Game.members[0].pos.y.fixed, off_b)                      = val_w;
        val_w                                                                           = FIELD(volatile s32, &g_Game.members[0].pos.z.fixed, off_a);
        FIELD(volatile s32, &g_Game.members[0].pos.z.fixed, off_a)                      = FIELD(volatile s32, &g_Game.members[0].pos.z.fixed, off_b);
        FIELD(volatile s32, &g_Game.members[0].pos.z.fixed, off_b)                      = val_w;
    }
    val_w                                                               = FIELD(volatile s32, &g_Game.members[0].unk_0C, off_a);
    FIELD(volatile s32, &g_Game.members[0].unk_0C, off_a)               = FIELD(volatile s32, &g_Game.members[0].unk_0C, off_b);
    FIELD(volatile s32, &g_Game.members[0].unk_0C, off_b)               = val_w;
    val_w                                                               = FIELD(volatile s32, &g_Game.members[0].unk_10, off_a);
    FIELD(volatile s32, &g_Game.members[0].unk_10, off_a)               = FIELD(volatile s32, &g_Game.members[0].unk_10, off_b);
    FIELD(volatile s32, &g_Game.members[0].unk_10, off_b)               = val_w;
    val_w                                                               = FIELD(volatile s32, &g_Game.members[0].unk_14, off_a);
    FIELD(volatile s32, &g_Game.members[0].unk_14, off_a)               = FIELD(volatile s32, &g_Game.members[0].unk_14, off_b);
    FIELD(volatile s32, &g_Game.members[0].unk_14, off_b)               = val_w;
    val_b                                                               = FIELD(volatile u8, &g_Game.members[0].u.turn.command.type, off_a);
    FIELD(volatile u8, &g_Game.members[0].u.turn.command.type, off_a)   = FIELD(volatile u8, &g_Game.members[0].u.turn.command.type, off_b);
    FIELD(volatile u8, &g_Game.members[0].u.turn.command.type, off_b)   = val_b;
    val_b                                                               = FIELD(volatile u8, &g_Game.members[0].u.turn.command.target, off_a);
    FIELD(volatile u8, &g_Game.members[0].u.turn.command.target, off_a) = FIELD(volatile u8, &g_Game.members[0].u.turn.command.target, off_b);
    FIELD(volatile u8, &g_Game.members[0].u.turn.command.target, off_b) = val_b;
    FIELD(volatile u8, &g_Game.members[0].unk_4B, off_a)                = 0xFF;
    FIELD(volatile u8, &g_Game.members[0].unk_4B, off_b)                = 0xFF;
}
#else
INCLUDE_ASM(Party_SwapBattlerRows);
#endif
