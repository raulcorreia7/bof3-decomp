#include "engine/slus/slus.h"

/* clears the four header bytes of the 0x140-stride record selected by character_index. */
MATCH void Party_BattlersClearState(s32 character_index) {
    u32 index;

    index                             = character_index & BYTE_MASK;
    g_Game.members[index].header.mode = 0;
    g_Game.members[index].header.step = 0;
    g_Game.members[index].unk_03      = 0;
    g_Game.members[index].unk_04      = 0;
}
