#include "game_00.h"

MATCH u8 func_8019EEE4(void) {
    s16 distance;
    s8  slot;
    u8  found;
    u32 roll;
    s32 index;

    found    = 0;
    distance = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    slot     = Actor_FindInRange(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0);
    if (slot != -1) {
        g_Actors[slot].interaction_flags |= ACTOR_INTERACTION_PENDING;
        return true;
    }
    if (COORD_INT(g_Game.members[0].pos.z) - distance >= 129) {
        return false;
    }
    if (distance - COORD_INT(g_Game.members[0].pos.z) >= 257) {
        return true;
    }
    if ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) == 0x11) {
        return true;
    }
    if ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) == 0xFD) {
        found = 1;
        Area_CellClear(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y));
    }
    if ((COORD_FRAC(SELF(Actor)->pos.x) != 0) && !found) {
        if ((Area_CellGetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) == 0xFD) {
            found = 1;
            Area_CellClear((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y));
        }
    }
    if ((COORD_FRAC(SELF(Actor)->pos.y) != 0) && !found && ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1)) & BYTE_MASK) == 0xFD)) {
        found = 1;
        Area_CellClear(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1));
    }
    if ((COORD_FRAC(SELF(Actor)->pos.x) != 0) && (COORD_FRAC(SELF(Actor)->pos.y) != 0) && !found) {
        if ((Area_CellGetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1)) & BYTE_MASK) == 0xFD) {
            found = 1;
            Area_CellClear((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1));
        }
    }
    if (found) {
        roll = RANDOM_MASK(0xF);
        if (roll >= 0xD) {
            SELF(Actor)->param.unk_0B = 2;
            if (roll == 0xF) {
                Game_RewardZenny(0xA);
            } else {
                Game_RewardZenny(5);
            }
            index = (s8)Actor_FindFreeSpawned();
            if (index != -1) {
                g_SpawnedActors[index].header.flags     = 1;
                g_SpawnedActors[index].type             = 0x34;
                g_SpawnedActors[index].header.mode      = 1;
                g_SpawnedActors[index].pos.x.fixed      = SELF(Actor)->pos.x.fixed;
                g_SpawnedActors[index].pos.y.fixed      = SELF(Actor)->pos.y.fixed;
                COORD_INT(g_SpawnedActors[index].pos.z) = Area_HeightSample(g_SpawnedActors[index].pos.x.fixed, g_SpawnedActors[index].pos.y.fixed) + 0x100;
                g_SpawnedActors[index].link             = 0;
            }
            g_Game.members[0].unk_07 = 1;
        } else {
            SELF(Actor)->param.unk_0B = 0;
        }
        return true;
    }
    return false;
}
