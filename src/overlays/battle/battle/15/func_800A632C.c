#include "battle_15.h"

MATCH void func_800A632C(void) {
    s32           decoded;
    u16           pad;
    u8*           value;
    volatile u16* pad_state;
    u8*           page_counter;
    u16*          effect_flag;

    value                                    = Resource_GetText(0x62);
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = value;
    pad_state                                = &g_InputPressed;
    decoded                                  = INPUT_REPEATED(*pad_state, (PADLright | PADLleft));
    pad                                      = *pad_state;
    if ((pad & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        page_counter = (u8*)&g_Battle.ui_state;
        *page_counter -= 1;
        return;
    }
    if ((pad & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0) {
        if (D_801463B4 == 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            g_BattleUIState += 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            g_BattleUIState -= 1;
        }
        return;
    }
    if (decoded & (PADLright | PADLleft)) {
        effect_flag = &D_801463B4;
        *effect_flag ^= 1;
    }
    /* Retail passes the unmasked 32-bit cursor expression; the shared u16
     * prototype would add a truncation the original does not have. */
    ((void (*)(s32, s32, s32))Menu_DrawCursorSprite)((D_801463B4 * 0x22) + 0xD5, 0x18, 0);
}
