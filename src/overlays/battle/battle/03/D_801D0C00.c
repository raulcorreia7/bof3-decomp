#include "battle_03.h"

/* Overlay head .data, 0x801D0C00..0x801D0C2C: the mode-handler table and
 * the entrance table the battle state machine copies to its stack. */

/* In-overlay dispatch targets (split assembly units). */

u32 D_801D0C00 = 0x10;

/* 0x801D0C04 */
/* D_801D0C04 */
BattlePhases g_BattlePhases = {
    (Callback)Battle_UpdateStep, (Callback)func_801D1C54, (Callback)Battle_UpdateTurnSetup,
    (Callback)Battle_UpdateTurns,       (Callback)Battle_UpdateRoundEnd, (Callback)Battle_UpdateResult,
};

/* 0x801D0C1C */
/* D_801D0C1C */
BattleEntrances g_BattleEntrances = {
    (Callback)Battle_OpenPanels,
    (Callback)Battle_WaitForUI,
    (Callback)Battle_InitPanels,
    (Callback)Battle_EnterIntro,
};
