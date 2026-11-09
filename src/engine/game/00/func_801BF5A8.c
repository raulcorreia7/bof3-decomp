#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801BF5A8(s32 x, s32 y, s32 party_slot) {
    u8     base;
    s32    off;
    s32    x;
    s32    y;
    Actor* rec;

    x = x;
    y = y;
    if (g_Game.party_size == 2) {
        base = g_PartyFormation + 1;
    } else if (g_Game.party_size == 3) {
        base = g_PartyFormation + 4;
    } else {
        base = g_PartyFormation;
    }
    if (s_CameraScrollDeltas[g_Battle.scroll_dir].dx != 0) {
        rec        = g_Task;
        off        = (((base & BYTE_MASK) * 3) + (party_slot & BYTE_MASK)) * 8;
        rec->pos.x = x + (FIELD(s32, D_80181CA8, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4));
        rec->pos.y = y + (FIELD(s32, &D_80181CAC, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dx / 4));
    } else {
        rec        = g_Task;
        off        = (((base & BYTE_MASK) * 3) + (party_slot & BYTE_MASK)) * 8;
        rec->pos.x = x - (FIELD(s32, &D_80181CAC, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4));
        rec->pos.y = y + (FIELD(s32, D_80181CA8, off) * (s_CameraScrollDeltas[g_Battle.scroll_dir].dy / 4));
    }
    COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
}
#else
INCLUDE_ASM(func_801BF5A8);
#endif
