#include "game_00.h"

MATCH void func_801BDBC4(void) {
    s32 i;
    s32 offset;
    s32 count;
    u8  found;

    found = 0;
    if (g_GameRequestFlags & 0x1) {
        i = 0;
        if (i < g_Game.party_size) {
            count  = g_Game.party_size;
            offset = 0;
        loop:
            if (g_Characters[(&g_Game.members[0].character_index)[offset]].status & STATUS_CONFUSED) {
                found = 1;
            }
            i++;
            offset += BATTLE_PARTY_STRIDE;
            if (i < count) {
                /* A structured loop would hoist the table bases. */
                goto loop;
            }
        }
    } else if (g_Characters[g_Game.members[0].character_index].status & STATUS_CONFUSED) {
        found = 1;
    }
    if (found != 0) {
        g_Game.input = (g_InputHeld & INPUT_ACTION_BUTTONS) | (((g_InputHeld & (PADLup | PADLright)) << 2) | ((g_InputHeld & (PADLdown | PADLleft)) >> 2));
    } else {
        g_Game.input = g_InputHeld;
    }
}
