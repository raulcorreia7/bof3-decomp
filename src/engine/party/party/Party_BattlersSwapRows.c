#include "engine/game/00/game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void Party_BattlersSwapRows(s32 slot_a, s32 slot_b, s32 skip_state) {
    PartyMember* a;
    PartyMember* b;
    u8           val_b;
    s32          val_w;

    a = &g_Game.members[slot_a & BYTE_MASK];
    b = &g_Game.members[slot_b & BYTE_MASK];

    val_b               = a->chr.character_id;
    a->chr.character_id = b->chr.character_id;
    b->chr.character_id = val_b;
    if (!(skip_state & BYTE_MASK)) {
        val_b                                = a->facing;
        a->facing                            = b->facing;
        b->facing                            = val_b;
        val_b                                = a->unk_29;
        a->unk_29                            = b->unk_29;
        b->unk_29                            = val_b;
        val_b                                = a->status.field.flags.unsigned_value;
        a->status.field.flags.unsigned_value = b->status.field.flags.unsigned_value;
        b->status.field.flags.unsigned_value = val_b;
        val_w                                = a->pos.x.fixed;
        a->pos.x.fixed                       = b->pos.x.fixed;
        b->pos.x.fixed                       = val_w;
        val_w                                = a->pos.y.fixed;
        a->pos.y.fixed                       = b->pos.y.fixed;
        b->pos.y.fixed                       = val_w;
        val_w                                = a->pos.z.fixed;
        a->pos.z.fixed                       = b->pos.z.fixed;
        b->pos.z.fixed                       = val_w;
    }
    val_w                    = a->unk_0C;
    a->unk_0C                = b->unk_0C;
    b->unk_0C                = val_w;
    val_w                    = a->unk_10;
    a->unk_10                = b->unk_10;
    b->unk_10                = val_w;
    val_w                    = a->unk_14;
    a->unk_14                = b->unk_14;
    b->unk_14                = val_w;
    val_b                    = a->u.turn.command.type;
    a->u.turn.command.type   = b->u.turn.command.type;
    b->u.turn.command.type   = val_b;
    val_b                    = a->u.turn.command.target;
    a->u.turn.command.target = b->u.turn.command.target;
    b->u.turn.command.target = val_b;
    a->unk_4B                = 0xFF;
    b->unk_4B                = 0xFF;
}
#else
INCLUDE_ASM(Party_BattlersSwapRows);
#endif
