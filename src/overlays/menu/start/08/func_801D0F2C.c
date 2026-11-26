#include "start_08.h"

/* Seeds the save image from one starting point of the D_801EBA44 table. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D0F2C(u8 start) {
    u8*       stage;
    u8*       cell;
    u8*       src;
    u8        member;
    u16       item;
    u8        kind;
    u8        id;
    u8        vital;
    s32       i;
    s32       j;
    SaveData* save;
    u8*       row;

    g_SaveData.area_id      = D_801EBA44[start].area;
    g_SaveData.entry_x      = D_801EBA44[start].entry_x;
    stage                   = g_PartyStage;
    g_SaveData.entry_y      = D_801EBA44[start].entry_y;
    g_SaveData.entry_facing = D_801EBA44[start].facing;
    src                     = D_801EBA44[start].party;
    for (i = 0; i < 3; i++) {
        member = src[i];
        if (member != 0xFF) {
            stage[i] = member & 0x7F;
        } else {
            stage[i] = 0xFF;
        }
    }
    if (start >= 9) {
        g_Characters[g_CharSlotView[7]].character_id         = 7;
        g_Characters[g_CharSlotView[7]].base.surprise_chance = 0x37;
        g_Characters[g_CharSlotView[7]].base.evasion         = 8;
        g_Characters[g_CharSlotView[7]].base.accuracy        = 0x64;
        g_Characters[D_80181B18].character_id                = 8;
        g_Characters[D_80181B18].base.evasion                = 0xC;
    }
    EMI_PartyLoadArchives(SP_REF(u8, 0), SP_REF(u8, 1), SP_REF(u8, 2), 0);
    g_PartySize = 0;
    src         = D_801EBA44[start].party;
    for (i = 0; i < 3; i++) {
        member = *src;
        if (member != 0xFF && (member & 0x80) == 0) {
            Party_MemberJoin(member);
        } else {
            g_PartyFieldOrder[i]  = 0xFF;
            g_PartyBattleOrder[i] = 0xFF;
        }
        src++;
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
        kind = item >> 8;
        id   = item & 0xFF;
        if (id != 0xFF) {
            Item_Add(kind, id, 1, 0);
        }
    }
    for (i = 0; i < 16; i++) {
        vital = D_801EBA44[start].vitals[i];
        if (vital != 0xFF) {
            Item_VitalAdd(vital);
        }
    }
    for (i = 0; i < 0x10; i++) {
        g_SaveData.scene_event_flags[i] = D_801EC214[start][i];
    }
    save = &g_SaveData;
    for (i = 0; i < SCENARIO_COUNT; i++) {
        row = g_SaveData.scene_flag_rows[i];
        if (i < start) {
            row[0]                           = D_801EC174[i][0];
            g_SaveData.scene_flag_rows[i][1] = D_801EC174[i][1];
            g_SaveData.scene_flag_rows[i][2] = D_801EC174[i][2];
            g_SaveData.scene_flag_rows[i][3] = D_801EC174[i][3];
            g_SaveData.scene_flag_rows[i][4] = D_801EC174[i][4];
            g_SaveData.scene_flag_rows[i][5] = D_801EC174[i][5];
            g_SaveData.scene_flag_rows[i][6] = D_801EC174[i][6];
            g_SaveData.scene_flag_rows[i][7] = D_801EC174[i][7];
        } else {
            save->scene_flag_rows[i][7] = 0;
            save->scene_flag_rows[i][6] = 0;
            save->scene_flag_rows[i][5] = 0;
            save->scene_flag_rows[i][4] = 0;
            save->scene_flag_rows[i][3] = 0;
            save->scene_flag_rows[i][2] = 0;
            save->scene_flag_rows[i][1] = 0;
            row[0]                      = 0;
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
        Char_AbilityAdd(0x97, D_80181B17, 0, 0);
    }
    for (i = 0; i < 3; i++) {
        D_801454F4[i][0] = 0;
        D_801454F4[i][1] = 0;
        D_801454F4[i][2] = 0;
    }
    cell = &D_801454FF;
    for (j = 0; j < 3; j++) {
        *cell-- = 0;
    }
}
#else
INCLUDE_ASM(func_801D0F2C);
#endif
