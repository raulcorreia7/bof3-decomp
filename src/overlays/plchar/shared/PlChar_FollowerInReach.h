#ifndef PLCHAR_FOLLOWER_IN_REACH_H
#define PLCHAR_FOLLOWER_IN_REACH_H

#include "battle/records.h"

MATCH s32 PlChar_FollowerInReach(u8 index) {
    s32 i;

    for (i = 1; i < g_PartySize; i++) {
        if (func_801BDD58(g_SpawnedActors[index].pos.x.fixed, g_SpawnedActors[index].pos.y.fixed, g_SpawnedActors[index].pos.z.part.integer + 0x200, 1, (Actor*)&g_Game.members[i])) {
            return 1;
        }
    }
    return 0;
}

#endif
