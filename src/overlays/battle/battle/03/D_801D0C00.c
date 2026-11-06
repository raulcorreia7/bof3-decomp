#include "battle_03.h"

/* Overlay head .data, 0x801D0C00..0x801D0C2C: the mode-handler table and
 * the entrance table the battle state machine copies to its stack. */

/* In-overlay dispatch targets (split assembly units). */

u32 D_801D0C00 = 0x10;

/* 0x801D0C04 */
/* D_801D0C04 */
BattlePhases g_BattlePhases = {
    (Callback)Battle_DispatchStep, (Callback)func_801D1C54, (Callback)func_801D2740,
    (Callback)func_801D2AA8,       (Callback)func_801D4AC0, (Callback)func_801D6774,
};

/* 0x801D0C1C */
/* D_801D0C1C */
BattleEntrances g_BattleEntrances = {
    (Callback)Battle_ReserveStagePanels,
    (Callback)Battle_WaitUIMode,
    (Callback)Battle_InitPanels,
    (Callback)Battle_EnterIntro,
};
