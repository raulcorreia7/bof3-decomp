#include "game_00.h"

MATCH s32 func_801C0E48(void) {
    u8  result;
    u8* record;
    u8  count;
    u8  next;
    u16 flags;
    u8* state;
    s32 slot;

    result = 0;
    if (D_80146262 == 0) {
        result = 1;
    } else {
        slot = D_80146262 - 1;
        if (g_Game.members[slot].header.mode == 1) {
            if (D_80146262 == 1) {
                flags           = g_AreaWalkFlags;
                g_AreaWalkFlags = flags & ~AREA_WALK_ENTRY_ACTIVE;
                result          = 1;
                if (g_Game.party_size == D_80146262) {
                    D_80146260        = 0;
                    g_Game.walk_flags = flags & ~(0x200 | AREA_WALK_ENTRY_ACTIVE);
                    return 0;
                }
            } else {
                result = 1;
            }
            g_AreaWalkFlags &= ~(AREA_WALK_BUSY(D_80146262));
        }
    }
    if (result) {
        state  = &D_80146262;
        count  = *state;
        next   = count + 1;
        record = &((u8*)g_Game.members)[count * BATTLE_PARTY_STRIDE];
        TASK_SET(record);
        g_Game.current = record;
        *state         = next;
        if (g_Game.party_size != 1) {
            if (next == g_Game.party_size) {
                g_AreaWalkFlags &= ~(AREA_WALK_ENTRY_ACTIVE | AREA_WALK_ACCEPT_LOCK);
                D_80146260 = 0;
                g_AreaWalkFlags &= ~(0x200 | AREA_WALK_ENTRY_ACTIVE | AREA_WALK_ACCEPT_LOCK);
            }
        }
    }
    return result;
}
