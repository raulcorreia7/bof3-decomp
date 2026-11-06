#include "start_08.h"

MATCH void func_801D177C(void) {
    s8         i;
    s8         j;
    Character* chr;

    D_80148655 = 0;
    D_80148662 = 0;
    D_80148663 = 0;
    D_80148664 = 0;
    D_8014866A = 0;
    D_80148669 = 0;
    D_80148668 = 0;
    D_80148665 = 0;
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        ((s8*)&D_80148668)[i] = 0;
    }
    for (i = 0; i < g_PartySize; i++) {
        Char_RebuildStats(&g_Characters[g_CharSlot[D_80144F5A[i]]]);
    }
    i = 0;
    while (i < (Party_CountOrder(PARTY_ORDER_KIND_WALKING) & BYTE_MASK)) {
        s_PartyCharacterIds[i] = D_80144F5A[i];
        D_801ED613[i]          = D_80144F5D[i];
        i++;
    }
    for (; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        s_PartyCharacterIds[i] = 0xFF;
        D_801ED613[i]          = 0xFF;
    }
    D_80148661 = 0;
    i          = 0;
    chr        = g_Characters;
    for (; i < 8; i++) {
        if (chr->hp < (chr->stats.max_hp >> 2)) {
            chr->status |= STATUS_LOW_HP;
        } else {
            chr->status &= ~STATUS_LOW_HP;
        }
        chr++;
    }
    for (i = 0; i < 5; i++) {
        s_ChoiceMenuCursors[i] = 0;
        s_ChoiceMenuValues[i]  = 0;
    }
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        u8* row;

        j   = 0;
        row = s_SkillOrderCursors[i];
        for (; j < 4; j++) {
            row[j] = 0;
        }
    }
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        u8* row0;
        u8* row1;

        j    = 0;
        row0 = s_SkillOrderKinds[i];
        row1 = s_SkillOrderGroups[i];
        for (; j < 6; j++) {
            row0[j] = 0;
            row1[j] = 0;
        }
    }
    D_801ED891 = 0;
    D_801ED890 = 0;
    if (D_80148660 == 1) {
        D_80148650 = 5;
        D_80148651 = 5;
    } else {
        func_801D1FDC();
        D_80148651 = 0;
        D_80148650++;
    }
}
