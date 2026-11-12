#include "shop_00.h"

MATCH s32 func_801E4C2C(s32 item_class) {
    u8* entry;
    u8  value;
    s32 enabled;

    switch (item_class & BYTE_MASK) {
        case 11:
            enabled = g_PartyMenuFlags & 0x8;
            break;
        case 12:
            enabled = SYS_TestFlag(g_SceneEventFlags, 108);
            break;
        case 13:
            enabled = g_PartyMenuFlags & 0x10;
            break;
        case 14:
            enabled = g_PartyMenuFlags & 0x20;
            break;
        default:
            /* Other classes scan the entry list after the flag tests. */
            goto scan;
    }
    if (enabled == 0) {
        /* Shares the scan's return-0 block, as retail does. */
        goto fail;
    }
    return 1;

scan:
    entry = D_801E5FC0[item_class & BYTE_MASK];
    value = *entry;
    if (value == GAME_NONE) {
        return 1;
    }
    do {
        if ((Party_HasSkill(value) & BYTE_MASK) == 0) {
            /* An entry that misses ends the scan. */
            goto fail;
        }
        entry++;
        value = *entry;
    } while (value != GAME_NONE);
    return 1;
fail:
    return 0;
}
