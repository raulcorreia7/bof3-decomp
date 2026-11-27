#include "battle_15.h"

/* func_8009AF84 */
MATCH void Battle_InitItemPanel(void) {
    volatile u8* work;
    u8           one;
    /* FAKE: retail holds the store constant in v1. */
    FAKE_REG(u8, two, "v1");
    /* FAKE: retail holds the row count in a3 across both row stores. */
    FAKE_REG(u8, eight, "a3");
    u8 group;
    u8 page_base;
    u8 cursor;

    work                   = g_BattleChoicePanel;
    one                    = 1u;
    two                    = 2u;
    work[0]                = one;
    g_BattleChoicePanel[3] = two;
    g_BattleChoicePanel[8] = two;

    group     = D_801454FD;
    page_base = D_801454FE;
    cursor    = D_801454FF;
    /* FAKE: basic-block boundary pins the row constant materialization. */
    do {
        eight = 8u;
    } while (0);
    g_BattleChoicePanel[2] = one;

    g_BattleChoicePanel[0xD]                      = 0xFFu;
    FAKE_VOLATILE(s16, g_BattleChoicePanel[4])    = -0xAA;
    g_BattleChoicePanel[1]                        = eight;
    g_BattleChoicePanel[9]                        = 0u;
    FAKE_VOLATILE(u16, g_BattleChoicePanel[0x10]) = 0u;
    FAKE_VOLATILE(u16, g_BattleChoicePanel[6])    = 0x3Fu;
    g_BattleChoicePanel[0xA]                      = group;
    g_BattleChoicePanel[0xB]                      = page_base;
    g_BattleChoicePanel[0xC]                      = cursor;
    /* FAKE: alias keeps the work base in the register. */
    FAKE_OPAQUE(work);
    work[0x6C]                = 0u;
    g_BattleChoicePanel[0x6D] = eight;
    g_BattleChoicePanel[0x6E] = 0u;
}
