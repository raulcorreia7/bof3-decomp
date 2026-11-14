#ifndef PLCHAR_FOLLOWER_IN_REACH_H
#define PLCHAR_FOLLOWER_IN_REACH_H

#include "battle/records.h"

typedef struct PlCharCheck {
    s32 pos_x; /* 0x00 */
    s32 pos_y; /* 0x04 */
    u8  pad_08[2];
    s16 z; /* 0x0A */
    u8  pad_0C[0x74 - 0x0C];
} PlCharCheck;

ASSERT_SIZE(PlCharCheck, 0x74);
ASSERT_OFFSET(PlCharCheck, pos_y, 0x04);
ASSERT_OFFSET(PlCharCheck, z, 0x0A);

extern PlCharCheck D_80143FFC[];

MATCH s32 PlChar_FollowerInReach(u8 index) {
    s32 i;

    for (i = 1; i < g_PartySize; i++) {
        if (func_801BDD58(D_80143FFC[index].pos_x, D_80143FFC[index].pos_y, D_80143FFC[index].z + 0x200, 1, (Actor*)&g_Game.members[i])) {
            return 1;
        }
    }
    return 0;
}

#endif
