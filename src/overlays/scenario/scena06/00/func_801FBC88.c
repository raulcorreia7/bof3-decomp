#include "scena06_00.h"
#include "sys/exe.h"

MATCH void func_801FBC88(void) {
    u8 i;

    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_GARR) {
            UI_MessageStartArea(MSG_SCENA06_022);
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_NINA_YOUNG) {
            UI_MessageStartArea(MSG_SCENA06_021);
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_MOMO) {
            UI_MessageStartArea(MSG_SCENA06_020);
        }
    }
    g_GameStateIndex        = 2;
    g_ScenarioState.step_05 = 0xC;
}
