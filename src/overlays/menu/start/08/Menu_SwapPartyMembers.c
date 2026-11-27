#include "start_08.h"

/* func_801DB04C */
MATCH u8 Menu_SwapPartyMembers(void) {
    u8  i;
    u8  tmp;
    u8  member;
    u8  reserve;
    u8  row;
    s32 from;
    s32 to;

    if (D_80148658[0] == D_80148658[2]) {
        if (D_80148658[0] == 0) {
            tmp                                      = g_UIPanelTasks[D_80148658[1] + 4].unk_0C;
            g_UIPanelTasks[D_80148658[1] + 4].unk_0C = g_UIPanelTasks[D_80148658[5] + 4].unk_0C;
            g_UIPanelTasks[D_80148658[5] + 4].unk_0C = tmp;
            Menu_SwapBytes4(&g_PartyFieldOrder[D_80148658[1]], &g_PartyFieldOrder[D_80148658[5]]);
            for (i = 0; i < 4; i++) {
                tmp                                   = s_SkillOrderCursors[D_80148658[1]][i];
                s_SkillOrderCursors[D_80148658[1]][i] = s_SkillOrderCursors[D_80148658[5]][i];
                s_SkillOrderCursors[D_80148658[5]][i] = tmp;
            }
            for (i = 0; i < 6; i++) {
                tmp                                  = s_SkillOrderTypes[D_80148658[1]][i];
                s_SkillOrderTypes[D_80148658[1]][i]  = s_SkillOrderTypes[D_80148658[5]][i];
                s_SkillOrderTypes[D_80148658[5]][i]  = tmp;
                tmp                                  = s_SkillOrderGroups[D_80148658[1]][i];
                s_SkillOrderGroups[D_80148658[1]][i] = s_SkillOrderGroups[D_80148658[5]][i];
                s_SkillOrderGroups[D_80148658[5]][i] = tmp;
            }
        } else {
            Menu_SwapBytes4(&D_801ED690[D_80148658[1]], &D_801ED690[D_80148658[5]]);
        }
        return 0xFF;
    }
    if (D_80148658[0] == 0) {
        row     = D_80148658[1];
        member  = g_PartyFieldOrder[D_80148658[1]];
        reserve = D_801ED690[D_80148658[5]];
    } else {
        row     = D_80148658[5];
        member  = g_PartyFieldOrder[D_80148658[5]];
        reserve = D_801ED690[D_80148658[1]];
    }
    if (g_Characters[g_CharSlot[member]].party_flags & 0x2) {
        return member;
    }
    if (g_Characters[g_CharSlot[reserve]].party_flags & 0x2) {
        return reserve;
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
    for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
        if (g_PartyFieldOrder[i] == member) {
            g_PartyFieldOrder[i] = reserve;
        }
        if (g_PartyBattleOrder[i] == member) {
            g_PartyBattleOrder[i] = reserve;
        }
    }
    /* FAKE: retail reads g_UIPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A as u8[]. */
    for (i = 0; i < ((u8*)&g_UIPanelTasks[12].unk_0A)[0]; i++) {
        if (D_801ED690[i] == reserve) {
            D_801ED690[i] = member;
        }
    }
    for (i = 0; i < 4; i++) {
        s_SkillOrderCursors[row][i] = 0;
    }
    for (i = 0; i < 6; i++) {
        s_SkillOrderTypes[row][i]  = 0;
        s_SkillOrderGroups[row][i] = 0;
    }
    return 0xFF;
}
