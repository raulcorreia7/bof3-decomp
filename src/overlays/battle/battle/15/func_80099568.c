#include "battle_15.h"

/* First byte of g_BattleChoicePanel (0x80148570); a scalar symbol emits the
 * direct %lo store form instead of materializing the array address. */

s32 func_8009AC18(void);

MATCH void func_80099568(void) {
    /* FAKE: stack_scratch reserves the retail 0x28 frame; no instruction
     * references it — keep the slot so the frame layout matches. */
    u8            stack_scratch[0x28];
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
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Resource_GetText(D_8014862E == 0 ? 0x30 : 0x32);
    input                                    = &g_InputPressed;
    trigger                                  = INPUT_REPEATED(*input, (PADLup | PADLdown));
    held                                     = *input;
    if ((held & D_80145AC4) != 0u) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        g_BattlePanelMode     = 1;
        g_BattleChoicePhase   = 3;
        g_BattleSelectionHead = 1;
        D_80148594            = 0;
        D_80148624            = 0;
        D_801483C0            = 1;
        D_801485DC            = 0;
        g_BattleUIStep        = 1;
        g_BattleUIState       = 0;
        D_80148574            = D_80148598;
        D_80148576            = D_8014859A;
        return;
    }
    if ((held & PADRleft) != 0u) {
        if ((func_8009AC18() & 0xFF) != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 7));
        return;
    }
    if ((held & D_80145AC2) != 0u) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        cursor_value       = D_8014859E;
        D_8014859C         = 0;
        D_801485A1         = 0;
        D_80148654         = 0;
        counter            = (u8*)&g_BattleUIState;
        counter_value      = *counter + 1;
        selection_value    = g_BattleItemRow;
        g_BattleListCursor = cursor_value;
        D_801485C3         = selection_value;
        *counter           = counter_value;
        return;
    }
    if ((trigger & PADLup) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        g_BattleItemRow = g_BattleItemRow - 1;
        if ((s8)g_BattleItemRow < 0) {
            g_BattleItemRow = 5;
        }
    }
    if ((trigger & PADLdown) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        MEM(u8, (u32)&g_BattleItemRow) += 1;
        if ((s8)MEM(u8, (u32)&g_BattleItemRow) >= 6) {
            MEM(u8, (u32)&g_BattleItemRow) = 0;
        }
    }
    D_8014859D = g_BattleItemRow;
}
