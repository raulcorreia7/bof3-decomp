#include "battle_15.h"

/* First byte of g_BattleChoicePanel (0x80148570); a scalar symbol emits the
 * direct %lo store form instead of materializing the array address. */

bool Battle_Unequip(void);

/* func_80099568 */
MATCH void Battle_SelectEquipRow(void) {
    /* FAKE: stack_scratch reserves the retail 0x28 frame; no instruction
     * references it — keep the slot so the frame layout matches. */
    u8            stack_scratch[40];
    volatile u16* input;
    u8*           counter;
    u8            cursor_value;
    u8            selection_value;
    u8            counter_value;
    u16           held;
    s32           trigger;

    (void)stack_scratch;
    if (g_BattlePanelMode == 0) {
        D_801485DC = 1;
        D_801485E0 = D_801485BC + 6;
        D_801485E2 = D_801485BE + (g_BattleItemRow * 13 + 0x57);
    } else {
        D_801485DC = 0;
    }
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = Message_GetText(D_8014862E == 0 ? 0x30 : 0x32);
    input                                           = &g_PadStates[0].pressed;
    trigger                                         = INPUT_REPEATED(*input, (PADLup | PADLdown));
    held                                            = *input;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_BattlePanelMode          = 1;
        g_BattleChoicePhase        = 3;
        g_BattleSelectionHead      = 1;
        D_80148594                 = 0;
        D_80148624                 = 0;
        D_801483C0                 = 1;
        D_801485DC                 = 0;
        g_Battle.ui_step           = 1;
        g_Battle.ui_mode           = 0;
        g_MenuPanelTasks[16].pos.x = D_80148598;
        g_MenuPanelTasks[16].pos.y = D_8014859A;
        return;
    }
    if ((held & PADRleft) != 0u) {
        if ((Battle_Unequip() & BYTE_MASK) != 0) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 3));
            return;
        }
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 3));
        cursor_value       = D_8014859E;
        D_8014859C         = 0;
        D_801485A1         = 0;
        D_80148654         = 0;
        counter            = (u8*)&g_Battle.ui_mode;
        counter_value      = *counter + 1;
        selection_value    = g_BattleItemRow;
        g_BattleListCursor = cursor_value;
        D_801485C3         = selection_value;
        *counter           = counter_value;
        return;
    }
    if ((trigger & PADLup) != 0) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_BattleItemRow = g_BattleItemRow - 1;
        if ((s8)g_BattleItemRow < 0) {
            g_BattleItemRow = 5;
        }
    }
    if ((trigger & PADLdown) != 0) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0));
        MEM(u8, (u32)&g_BattleItemRow) += 1;
        if ((s8)MEM(u8, (u32)&g_BattleItemRow) >= 6) {
            MEM(u8, (u32)&g_BattleItemRow) = 0;
        }
    }
    D_8014859D = g_BattleItemRow;
}
