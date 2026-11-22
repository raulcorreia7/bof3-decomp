#include "engine/game/00/game_00.h"

MATCH void Party_BattlersSwapRows(s32 slot_a, s32 slot_b, s32 skip_state) {
    u8  val_b;
    s32 val_w;

    val_b                                       = g_Game.members[(u8)slot_a].chr.character_id;
    g_Game.members[(u8)slot_a].chr.character_id = g_Game.members[(u8)slot_b].chr.character_id;
    g_Game.members[(u8)slot_b].chr.character_id = val_b;
    if (!(skip_state & BYTE_MASK)) {
        val_b                                                        = g_Game.members[(u8)slot_a].facing;
        g_Game.members[(u8)slot_a].facing                            = g_Game.members[(u8)slot_b].facing;
        g_Game.members[(u8)slot_b].facing                            = val_b;
        val_b                                                        = g_Game.members[(u8)slot_a].unk_29;
        g_Game.members[(u8)slot_a].unk_29                            = g_Game.members[(u8)slot_b].unk_29;
        g_Game.members[(u8)slot_b].unk_29                            = val_b;
        val_b                                                        = g_Game.members[(u8)slot_a].status.field.flags.unsigned_value;
        g_Game.members[(u8)slot_a].status.field.flags.unsigned_value = g_Game.members[(u8)slot_b].status.field.flags.unsigned_value;
        g_Game.members[(u8)slot_b].status.field.flags.unsigned_value = val_b;
        val_w                                                        = g_Game.members[(u8)slot_a].pos.x.fixed;
        g_Game.members[(u8)slot_a].pos.x.fixed                       = g_Game.members[(u8)slot_b].pos.x.fixed;
        g_Game.members[(u8)slot_b].pos.x.fixed                       = val_w;
        val_w                                                        = g_Game.members[(u8)slot_a].pos.y.fixed;
        g_Game.members[(u8)slot_a].pos.y.fixed                       = g_Game.members[(u8)slot_b].pos.y.fixed;
        g_Game.members[(u8)slot_b].pos.y.fixed                       = val_w;
        val_w                                                        = g_Game.members[(u8)slot_a].pos.z.fixed;
        g_Game.members[(u8)slot_a].pos.z.fixed                       = g_Game.members[(u8)slot_b].pos.z.fixed;
        g_Game.members[(u8)slot_b].pos.z.fixed                       = val_w;
    }
    val_w                                            = g_Game.members[(u8)slot_a].unk_0C;
    g_Game.members[(u8)slot_a].unk_0C                = g_Game.members[(u8)slot_b].unk_0C;
    g_Game.members[(u8)slot_b].unk_0C                = val_w;
    val_w                                            = g_Game.members[(u8)slot_a].unk_10;
    g_Game.members[(u8)slot_a].unk_10                = g_Game.members[(u8)slot_b].unk_10;
    g_Game.members[(u8)slot_b].unk_10                = val_w;
    val_w                                            = g_Game.members[(u8)slot_a].unk_14;
    g_Game.members[(u8)slot_a].unk_14                = g_Game.members[(u8)slot_b].unk_14;
    g_Game.members[(u8)slot_b].unk_14                = val_w;
    val_b                                            = g_Game.members[(u8)slot_a].u.turn.command.type;
    g_Game.members[(u8)slot_a].u.turn.command.type   = g_Game.members[(u8)slot_b].u.turn.command.type;
    g_Game.members[(u8)slot_b].u.turn.command.type   = val_b;
    val_b                                            = g_Game.members[(u8)slot_a].u.turn.command.target;
    g_Game.members[(u8)slot_a].u.turn.command.target = g_Game.members[(u8)slot_b].u.turn.command.target;
    g_Game.members[(u8)slot_b].u.turn.command.target = val_b;
    g_Game.members[(u8)slot_a].unk_4B                = 0xFF;
    g_Game.members[(u8)slot_b].unk_4B                = 0xFF;
}
