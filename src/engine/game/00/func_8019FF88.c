#include "game_00.h"

MATCH void func_8019FF88(s32 entry_mode, s32 entry_index, s32 entry_flags) {
    s32 i;

    if (entry_mode & 0xFF) {
        g_AreaWalkFlags |= AREA_WALK_ENTRY_ACTIVE;
    }
    D_80146260 = 1;
    D_80146261 = entry_mode;
    D_80146262 = 0;
    D_80146264 = entry_index;
    D_80146268 = entry_flags;
    for (i = 0; i < g_PartySize; i++) {
        D_80145FBB[i].mode = s_EntityModes[entry_mode & 0xFF];
        D_80145FBB[i].flags |= 0x2;
    }
}
