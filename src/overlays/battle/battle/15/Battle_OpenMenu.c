#include "battle_15.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */

/* opens the battle menu pair, primes the shared timers and request
 * word, then unpacks the 18-bit panel flag mask into the 3x6 flag table and
 * advances the battle frame step.
 */
/* func_800A47AC */
MATCH void Battle_OpenMenu(void) {
    u8 row;
    u8 col;
    /* FAKE: retain early menu argument. */
    FAKE_REG(s32, menu_id, "a0");
    volatile u32* mask;
    u8(*flags)[6];
    u32 shifted_mask;

    Menu_OpenPanelTask(0x15, 5);
    menu_id    = 0x11;
    D_80148628 = 0x142;
    D_80148626 = 0;
    D_80148627 = 0;
    D_8014862A = 0x3F;
    D_8014862E = 0;
    /* FAKE: hold second argument. */
    FAKE_BARRIER();
    Menu_OpenPanelTask(menu_id, 5);
    D_80148596 = 1;
    D_80148597 = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
    row   = 0;
    flags = D_800B7070;
    mask  = &D_80145548;
    for (; row < 3U; row++) {
        for (col = 0; col < 6U; col++) {
            shifted_mask    = (*mask) >> (row * 6 + col);
            flags[row][col] = shifted_mask & 0x1;
        }
    }
    g_InputRepeatButtons        = 0;
    g_Battle.row_cursor         = 1;
    g_Battle.cursor.panel_entry = 0;
    D_801462E7                  = 0;
    D_801463B2                  = 0;
    D_801463B4                  = 0;
    g_Battle.gene_count         = 0;
    *D_801463B8                 = 0;
    Battle_SetGeneCount();
    g_Battle.ui_state = 0;
    g_BattleUIStep_nv = g_BattleUIStep_nv + 1;
}
