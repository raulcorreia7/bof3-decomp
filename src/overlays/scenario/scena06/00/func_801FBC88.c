#include "scena06_00.h"
#include "sys/exe.h"

MATCH void func_801FBC88(void) {
    u8 i;

    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_GARR) {
            Message_StartAreaMessage(0x16);
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_NINA_YOUNG) {
            Message_StartAreaMessage(0x15);
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_MOMO) {
            Message_StartAreaMessage(0x14);
        }
    }
    g_GameStateIndex = 2;
    D_80146875       = 0xC;
}
