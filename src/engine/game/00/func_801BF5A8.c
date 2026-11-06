#include "game_00.h"

/* nonmatching unmeasured: tried cleaned first-draft temps (frame now 0x18 like retail), signed /4; 40.50%: retail rereads
 * g_BattleScrollDir after the 0x34 store and folds the table symbol into the displacement (lui at; addu at,at,index;
 * lb); mine hoists &D_801CD458[index*2] and CSEs it; x is copied to t2 in retail. */
#ifdef NON_MATCHING
NON_MATCHING void func_801BF5A8(s32 x, s32 y, s32 party_slot) {
    u8     base;
    s32    off;
    s32    x;
    s32    y;
    Actor* rec;

    x = x;
    y = y;
    if (g_PartySize == 2) {
        base = g_PartyFormation + 1;
    } else if (g_PartySize == 3) {
        base = g_PartyFormation + 4;
    } else {
        base = g_PartyFormation;
    }
    if (s_CameraScrollDeltas[g_BattleScrollDir * 2] != 0) {
        rec        = g_Task;
        off        = (((base & 0xFF) * 3) + (party_slot & 0xFF)) * 8;
        rec->pos.x = x + (FIELD(s32, D_80181CA8, off) * (s_CameraScrollDeltas[g_BattleScrollDir * 2] / 4));
        rec->pos.y = y + (FIELD(s32, &D_80181CAC, off) * (s_CameraScrollDeltas[g_BattleScrollDir * 2] / 4));
    } else {
        rec        = g_Task;
        off        = (((base & 0xFF) * 3) + (party_slot & 0xFF)) * 8;
        rec->pos.x = x - (FIELD(s32, &D_80181CAC, off) * (D_801CD459[g_BattleScrollDir * 2] / 4));
        rec->pos.y = y + (FIELD(s32, D_80181CA8, off) * (D_801CD459[g_BattleScrollDir * 2] / 4));
    }
    COORD_INT(g_Task->depth) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
}
#else
INCLUDE_ASM(func_801BF5A8);
#endif
