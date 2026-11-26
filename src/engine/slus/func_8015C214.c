#include "engine/slus/slus.h"

/* writes the 0x140-stride record flags selected by slot.
 */
MATCH void func_8015C214(s32 slot, u8 value) {
    u32 index;

    index                              = slot & BYTE_MASK;
    g_Game.members[index].header.mode  = 2;
    g_Game.members[index].header.step  = PARTY_MOVE_STEP_FLOOR_DAMAGE;
    g_Game.members[index].unk_03       = 0;
    g_Game.members[index].param.unk_0B = value;
}
