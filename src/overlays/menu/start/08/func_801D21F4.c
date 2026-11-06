#include "start_08.h"

MATCH void func_801D21F4(void) {
    u8 saved[PARTY_SLOT_COUNT][3];
    u8 i;
    u8 j;
    u8 count;
    u8 unmatched;

    count = 0;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (s_PartyCharacterIds[i] != CHAR_ID_BLANK) {
            j = 0;
            do {
                if (g_PartyFieldOrder[j] != CHAR_ID_BLANK && s_PartyCharacterIds[i] == g_PartyFieldOrder[j]) {
                    unmatched = 0;
                    goto add; /* a match skips the not-found flag */
                }
                j++;
                unmatched = 1;
            } while (j < PARTY_SLOT_COUNT);
        add:
            count += unmatched;
        }
    }
    if (count != 0)
        D_80148661 = 1;
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        for (j = 0; j < 3; j++)
            saved[i][j] = D_801454F4[i][j];
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyBattleOrder[i] != CHAR_ID_BLANK) {
            j = 0;
            do {
                if (D_801ED613[j] != CHAR_ID_BLANK && g_PartyBattleOrder[i] == D_801ED613[j]) {
                    D_801454F4[i][0] = saved[j][0];
                    D_801454F4[i][1] = saved[j][1];
                    D_801454F4[i][2] = saved[j][2];
                    unmatched        = 0;
                    goto rewritten; /* a match skips the not-found flag */
                }
                j++;
                unmatched = 1;
            } while (j < PARTY_SLOT_COUNT);
        rewritten:
            if (unmatched != 0) {
                D_801454F4[i][0] = 0;
                D_801454F4[i][1] = 0;
                D_801454F4[i][2] = 0;
            }
        }
    }
}
