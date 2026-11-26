#include "area111_13.h"

/* Reads the cell the lead party member stands on and turns the lead's facing to
 * the direction the cell's event record asks for. */
MATCH void func_801F35F4(void) {
    u8  col;
    u8  row;
    u8  cell;
    u8  actor_index;
    u8  slot;
    u16 cursor;

    col = (g_Game.members[0].pos.x.part.integer - 11) / 2;
    row = (g_Game.members[0].pos.y.part.integer - 177) / 2;
    if ((col & 1) != 0) {
        cell = D_801F5C18[row][col / 2] & 0xF;
    } else {
        cell = D_801F5C18[row][col / 2] >> 4;
    }
    actor_index = cell - 1;
    if (actor_index != 0xFF) {
        slot   = (u8)(g_GameState - g_Game.members + 1);
        cursor = g_ScriptState->cursor;
        func_801AC768(g_ScriptState, 7, actor_index, slot, 16);
        g_ScriptState->cursor  = cursor;
        cell                   = g_PartyActors[actor_index].direction & 7;
        SELF(Actor)->direction = cell;
        D_80143F50             = cell;
    }
}
