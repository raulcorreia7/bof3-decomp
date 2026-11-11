#ifndef PLCHAR_FUNC_801CF808_H
#define PLCHAR_FUNC_801CF808_H

MATCH s32 func_801CF808(u8 index) {
    s32 i;

    s32 x = D_80143FFC[index].pos_x + g_FacingSteps[g_Task->direction_08].x * 2;
    s32 y = D_80143FFC[index].pos_y + g_FacingSteps[g_Task->direction_08].y * 2;
    for (i = 1; i < g_PartySize; i++) {
        if (func_801BDD58(x, y, D_80143FFC[index].z, 1, (Actor*)&g_Game.members[i]) & 0xFF) {
            return 1;
        }
    }
    return 0;
}

#endif
