#ifndef PLCHAR_FOLLOWER_IN_REACH_CHECK_H
#define PLCHAR_FOLLOWER_IN_REACH_CHECK_H

#ifndef PLCHAR_CHECK_RECORD_DEFINED
#define PLCHAR_CHECK_RECORD_DEFINED

typedef struct PlcharCheckRecord {
    s32 pos_x;
    s32 pos_y;
    u8  pad_08[2];
    s16 z;
    u8  pad_0C[0x74 - 0x0C];
} PlcharCheckRecord;
#endif

extern PlcharCheckRecord D_80143FFC[];
extern u8                g_PartySize;

MATCH s32 Plchar_FollowerInReach(u8 index) {
    s32 i;

    for (i = 1; i < g_PartySize; i++) {
        if (func_801BDD58(D_80143FFC[index].pos_x, D_80143FFC[index].pos_y, D_80143FFC[index].z + 0x200, 1, (Actor*)&g_Game.members[i]) & 0xFF) {
            return 1;
        }
    }
    return 0;
}

#endif
