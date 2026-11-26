#include "area111_13.h"

MATCH void func_801F39E0(void) {
    u8  x;
    u8  y;
    u8  facing;
    u8  selection;
    u8  party;
    u16 cursor;

    y      = (g_PartyActors[LOBU(SELF(Actor)->unk_18)].pos.y.part.integer - 177) / 2;
    x      = (g_PartyActors[LOBU(SELF(Actor)->unk_18)].pos.x.part.integer - 11) / 2;
    facing = SELF(Actor)->direction & 7;
    x += D_80181B00[facing][0];
    y += D_80181B00[facing][1];
    if (x >= 7) {
        return;
    }
    if (y >= 7) {
        return;
    }
    if (x & 1) {
        selection = D_801F5C18[y][x >> 1] & 0xF;
    } else {
        selection = D_801F5C18[y][x >> 1] >> 4;
    }
    selection -= 1;
    if (selection >= 4) {
        return;
    }
    cursor = g_ScriptState->cursor;
    party  = (g_GameState - g_Game.members) + 1;
    func_801AC768(g_ScriptState, 7, selection, party, 0xC);
    g_ScriptState->cursor              = cursor;
    g_PartyActors[selection].direction = SELF(Actor)->direction & 7;
    g_ScriptState->cursor -= 6;
}
