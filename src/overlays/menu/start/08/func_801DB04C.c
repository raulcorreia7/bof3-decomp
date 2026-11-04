#include "start_08.h"

extern s8 D_80148658[6]; /* local: six s8 cursor bytes; sibling copies read them one by one */

MATCH u8 func_801DB04C(void) {
    u8  i;
    u8  tmp;
    u8  member;
    u8  reserve;
    u8  row;
    s32 from;
    s32 to;

    if (D_80148658[0] == D_80148658[2]) {
        if (D_80148658[0] == 0) {
            tmp                              = D_8014833C[D_80148658[1] + 4][0];
            D_8014833C[D_80148658[1] + 4][0] = D_8014833C[D_80148658[5] + 4][0];
            D_8014833C[D_80148658[5] + 4][0] = tmp;
            Menu_SwapBytes_801DAC08(&D_80144F5A[D_80148658[1]], &D_80144F5A[D_80148658[5]]);
            for (i = 0; i < 4; i++) {
                tmp                                   = s_SkillOrderCursors[D_80148658[1]][i];
                s_SkillOrderCursors[D_80148658[1]][i] = s_SkillOrderCursors[D_80148658[5]][i];
                s_SkillOrderCursors[D_80148658[5]][i] = tmp;
            }
            for (i = 0; i < 6; i++) {
                tmp                                  = s_SkillOrderKinds[D_80148658[1]][i];
                s_SkillOrderKinds[D_80148658[1]][i]  = s_SkillOrderKinds[D_80148658[5]][i];
                s_SkillOrderKinds[D_80148658[5]][i]  = tmp;
                tmp                                  = s_SkillOrderGroups[D_80148658[1]][i];
                s_SkillOrderGroups[D_80148658[1]][i] = s_SkillOrderGroups[D_80148658[5]][i];
                s_SkillOrderGroups[D_80148658[5]][i] = tmp;
            }
        } else {
            Menu_SwapBytes_801DAC08(&D_801ED690[D_80148658[1]], &D_801ED690[D_80148658[5]]);
        }
        return 0xFF;
    }
    if (D_80148658[0] == 0) {
        row     = D_80148658[1];
        member  = D_80144F5A[D_80148658[1]];
        reserve = D_801ED690[D_80148658[5]];
    } else {
        row     = D_80148658[5];
        member  = D_80144F5A[D_80148658[5]];
        reserve = D_801ED690[D_80148658[1]];
    }
    if (g_Characters[g_CharSlot[member]].unk_07 & 2) {
        return member;
    }
    if (g_Characters[g_CharSlot[reserve]].unk_07 & 2) {
        return reserve;
    }
    SND_PlayCue(EMI_CUE_ID(1, 3));
    for (i = 0; i < Party_CountOrder(0); i++) {
        if (D_80144F5A[i] == member) {
            D_80144F5A[i] = reserve;
        }
        if (D_80144F5D[i] == member) {
            D_80144F5D[i] = reserve;
        }
    }
    /* FAKE: retail reads D_801484EA as u8[]. */
    for (i = 0; i < ((u8*)&D_801484EA)[0]; i++) {
        if (D_801ED690[i] == reserve) {
            D_801ED690[i] = member;
        }
    }
    for (i = 0; i < 4; i++) {
        s_SkillOrderCursors[row][i] = 0;
    }
    for (i = 0; i < 6; i++) {
        s_SkillOrderKinds[row][i]  = 0;
        s_SkillOrderGroups[row][i] = 0;
    }
    return 0xFF;
}
