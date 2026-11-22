#include "start_08.h"

/* Sets up the save image of a new game from one starting point of the
 * D_801EBA44 table. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D0F2C(u8 start) {
    u8* sp;
    u8* src;
    u8* rows;
    u8  member;
    u16 item;
    u8  vital;
    s32 i;
    s32 j;
    s32 idx;
    u8* row;

    g_SaveAreaId = D_801EBA44[start].area;
    g_SaveEntryX = D_801EBA44[start].entry_x;
    /* FAKE: FAKE_ORDER_FENCE keeps the entry index ahead of the scratchpad address; retail forms the index first. */
    FAKE_ORDER_FENCE();
    sp                = SP(0);
    g_SaveEntryY      = D_801EBA44[start].entry_y;
    g_SaveEntryFacing = D_801EBA44[start].facing;
    src               = D_801EBA44[start].party;
    for (i = 0; i < 3; i++) {
        member = *src++;
        if (member != 0xFF) {
            *sp = member & 0x7F;
        } else {
            *sp = 0xFF;
        }
        sp++;
    }
    if (start >= 9) {
        u8* character = &D_80181B17;

        g_Characters[*character].character_id         = 7;
        g_Characters[*character].base.surprise_chance = 0x37;
        g_Characters[*character].base.evasion         = 8;
        g_Characters[*character].base.accuracy        = 0x64;
        g_Characters[D_80181B18].character_id         = 8;
        g_Characters[D_80181B18].base.evasion         = 0xC;
    }
    EMI_PartyLoadArchives(SP_REF(u8, 0), SP_REF(u8, 1), SP_REF(u8, 2), 0);
    g_PartySize = 0;
    src         = D_801EBA44[start].party;
    for (i = 0; i < 3; i++) {
        member = *src++;
        if (member != 0xFF && (member & 0x80) == 0) {
            Party_JoinMember(member);
        } else {
            g_PartyFieldOrder[i]  = 0xFF;
            g_PartyBattleOrder[i] = 0xFF;
        }
    }
    for (i = 0; i < 7; i++) {
        g_Characters[i].party_flags |= D_801EBA44[start].party_flags[i];
        if (D_801EBA44[start].exp[i] != 0) {
            g_Characters[i].exp = D_801EBA44[start].exp[i];
        }
        Char_ApplyLevelUps((u8)i);
    }
    Char_RebuildPartyStats();
    g_Zenny = D_801EBA44[start].zenny;
    for (i = 0; i < 8; i++) {
        item = D_801EBA44[start].items[i];
        if ((item & 0xFF) != 0xFF) {
            Item_Add(item >> 8, item & 0xFF, 1, 0);
        }
    }
    for (i = 0; i < 16; i++) {
        vital = D_801EBA44[start].vitals[i];
        if (vital != 0xFF) {
            Item_VitalAdd(vital);
        }
    }
    for (i = 0; i < 0x10; i++) {
        g_SceneEventFlags[i] = D_801EC214[start * 0x10 + i];
    }
    for (i = 0; i < 0x14; i++) {
        idx = i * 8;
        if (i < start) {
            g_SceneFlagWords[idx + 0] = D_801EC174[idx + 0];
            g_SceneFlagWords[idx + 1] = D_801EC174[idx + 1];
            g_SceneFlagWords[idx + 2] = D_801EC174[idx + 2];
            g_SceneFlagWords[idx + 3] = D_801EC174[idx + 3];
            g_SceneFlagWords[idx + 4] = D_801EC174[idx + 4];
            g_SceneFlagWords[idx + 5] = D_801EC174[idx + 5];
            g_SceneFlagWords[idx + 6] = D_801EC174[idx + 6];
            g_SceneFlagWords[idx + 7] = D_801EC174[idx + 7];
        } else {
            row    = g_SceneFlagWords + idx;
            row[0] = 0;
            row[1] = 0;
            row[2] = 0;
            row[3] = 0;
            row[4] = 0;
            row[5] = 0;
            row[6] = 0;
            row[7] = 0;
        }
    }
    for (i = 0; i < 6; i++) {
        for (j = 3; j >= 0; j--) {
            g_BattleTargetRows[i][j] = 0xFF;
        }
    }
    for (i = 0; i < 0xC; i++) {
        for (j = 3; j >= 0; j--) {
            D_80145518[i][j] = 0xFF;
        }
    }
    D_80145548 = D_801EBA44[start].unk_58;
    if (D_801EBA44[start].unk_58 != 0) {
        Char_AddAbility(0x97, D_80181B17, 0, 0);
    }
    for (i = 0; i < 3; i++) {
        D_801454F4[i][0] = 0;
        D_801454F4[i][1] = 0;
        D_801454F4[i][2] = 0;
    }
    rows = &D_801454FF;
    for (i = 0; i < 3; i++) {
        *rows-- = 0;
    }
}
#else
INCLUDE_ASM(func_801D0F2C);
#endif
