#include "game_00.h"

#define WORK ((Actor*)g_Task)

MATCH u8 func_8019EEE4(void) {
    s16 distance;
    s8  slot;
    u8  found;
    u32 roll;
    s32 index;

    found    = 0;
    distance = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    slot     = func_801BDE14(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;
        return true;
    }
    if (D_80145ECE - distance >= 0x81) {
        return false;
    }
    if (distance - D_80145ECE >= 0x101) {
        return true;
    }
    if ((Area_GetCellCode(COORD_INT(WORK->pos.x), COORD_INT(WORK->pos.y)) & BYTE_MASK) == 0x11) {
        return true;
    }
    if ((Area_GetCellCode(COORD_INT(WORK->pos.x), COORD_INT(WORK->pos.y)) & BYTE_MASK) == 0xFD) {
        found = 1;
        Area_ClearCell(COORD_INT(WORK->pos.x), COORD_INT(WORK->pos.y));
    }
    if ((COORD_FRAC(WORK->pos.x) != 0) && !found) {
        if ((Area_GetCellCode((s16)((u16)COORD_INT(WORK->pos.x) + 1), COORD_INT(WORK->pos.y)) & BYTE_MASK) == 0xFD) {
            found = 1;
            Area_ClearCell((s16)((u16)COORD_INT(WORK->pos.x) + 1), COORD_INT(WORK->pos.y));
        }
    }
    if ((COORD_FRAC(WORK->pos.y) != 0) && !found &&
        ((Area_GetCellCode(COORD_INT(WORK->pos.x), (s16)((u16)COORD_INT(WORK->pos.y) + 1)) & BYTE_MASK) == 0xFD)) {
        found = 1;
        Area_ClearCell(COORD_INT(WORK->pos.x), (s16)((u16)COORD_INT(WORK->pos.y) + 1));
    }
    if ((COORD_FRAC(WORK->pos.x) != 0) && (COORD_FRAC(WORK->pos.y) != 0) && !found) {
        if ((Area_GetCellCode((s16)((u16)COORD_INT(WORK->pos.x) + 1), (s16)((u16)COORD_INT(WORK->pos.y) + 1)) &
             BYTE_MASK) == 0xFD) {
            found = 1;
            Area_ClearCell((s16)((u16)COORD_INT(WORK->pos.x) + 1), (s16)((u16)COORD_INT(WORK->pos.y) + 1));
        }
    }
    if (found) {
        roll = RANDOM_MASK(0xF);
        if (roll >= 0xD) {
            g_Task->unk_0B = 2;
            if (roll == 0xF) {
                func_801B5E58(0xA);
            } else {
                func_801B5E58(5);
            }
            index = (s8)Actor_FindFreeSlot();
            if (index != -1) {
                g_ActorSlots[index].header.flags = 1;
                g_ActorSlots[index].type         = 0x34;
                g_ActorSlots[index].header.mode  = 1;
                g_ActorSlots[index].x.fixed      = g_Task->pos.x.fixed;
                g_ActorSlots[index].y.fixed      = g_Task->pos.y.fixed;
                COORD_INT(g_ActorSlots[index].z) =
                    Area_SampleHeight(g_ActorSlots[index].x.fixed, g_ActorSlots[index].y.fixed) + 0x100;
                g_ActorSlots[index].link = 0;
            }
            g_BattlePartyBattlers[0].unk_07 = 1;
        } else {
            g_Task->unk_0B = 0;
        }
        return true;
    }
    return false;
}
