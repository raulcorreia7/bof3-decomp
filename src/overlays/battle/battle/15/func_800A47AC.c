#include "battle_15.h"

/* FAKE: a second symbol forces the separate %hi/%lo load retail has. */

/* opens the battle menu pair, primes the shared timers and request
 * word, then unpacks the 18-bit panel flag mask into the 3x6 flag table and
 * advances the battle frame step.
 */
MATCH void func_800A47AC(void) {
    u8 row;
    u8 col;
    /* FAKE: retain early menu argument. */
    MATCH_FAKE_PIN(s32, menu_id, "a0");
    volatile u32* mask;
    u8(*flags)[6];
    u32 shifted_mask;

    Menu_ArmPanelTask(0x15, 5);
    menu_id    = 0x11;
    D_80148628 = 0x142;
    D_80148626 = 0;
    D_80148627 = 0;
    D_8014862A = 0x3F;
    D_8014862E = 0;
    /* FAKE: hold second argument. */
    MATCH_FAKE_BARRIER();
    Menu_ArmPanelTask(menu_id, 5);
    D_80148596 = 1;
    D_80148597 = 0;
    SND_PlayCue(EMI_CUE_ID(1, 2));
    row   = 0;
    flags = D_800B7070;
    mask  = &D_80145548;
    for (; row < 3U; row++) {
        for (col = 0; col < 6U; col++) {
            shifted_mask    = (*mask) >> (row * 6 + col);
            flags[row][col] = shifted_mask & 1;
        }
    }
    g_InputRepeatButtons = 0;
    g_BattleRowCursor    = 1;
    g_BattlePanelEntry   = 0;
    D_801462E7           = 0;
    D_801463B2           = 0;
    D_801463B4           = 0;
    *g_BattleGeneCount   = 0;
    *D_801463B8          = 0;
    func_800A82F8();
    g_BattleUIState   = 0;
    g_BattleUIStep_nv = g_BattleUIStep_nv + 1;
}
