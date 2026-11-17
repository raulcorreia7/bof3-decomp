#include "battle_03.h"

/* Overlay head .data, 0x801D0F20..0x801D1014: the panel, preview and
 * result handler tables the overlay dispatches through. */

/* In-overlay dispatch targets (split assembly units). */
extern void func_801EA254(void), func_801EA530(void);

/* 0x801D0F20 */
BattleEffect0Steps D_801D0F20 = {
    (Callback)func_801E6420,
    (Callback)func_801E64B4,
    (Callback)func_801E65F8,
};

/* 0x801D0F2C */
BattleEffect1Steps D_801D0F2C = {
    (Callback)func_801E6990,
    (Callback)func_801E69C0,
    (Callback)func_801E6A54,
};

/* 0x801D0F38 */
BattleEffect2Steps D_801D0F38 = {
    (Callback)func_801E6B28,
    (Callback)func_801E6BC8,
    (Callback)func_801E6C20,
};

/* 0x801D0F44 */
BattleEffect3Steps D_801D0F44 = {
    (Callback)func_801E6D28, (Callback)func_801E6E54, (Callback)func_801E6FA0, (Callback)func_801E6FB0, (Callback)func_801E71EC,
};

/* 0x801D0F58 */
BattleEffect4Steps D_801D0F58 = {
    (Callback)func_801E7528, (Callback)func_801E7558, (Callback)func_801E75B0, (Callback)func_801E7634, (Callback)func_801E7778,
};

/* 0x801D0F6C */
BattleSavedPreviewModes D_801D0F6C = {
    (Callback)func_801E7888, (Callback)func_801E78F0, (Callback)Battle_StartCharacterLoad, (Callback)func_801E7BA0, (Callback)func_801E8558,
};

/* 0x801D0F80 */
/* D_801D0F80 */
BattlePanelModes g_BattlePanelModes = {
    (Callback)Battle_UpdatePartyPanel, (Callback)Battle_UpdateMenuRowsPanel, (Callback)func_801E943C,           (Callback)func_801E94D0,
    (Callback)Battle_UpdateEnemyPanel, (Callback)Battle_UpdateMemberPanel,   (Callback)Battle_UpdateEventPanel, (Callback)Battle_UpdateMessagePanel,
};

/* 0x801D0FA0 */
BattlePartyPanelSteps g_BattlePartyPanelSteps = {
    (Callback)Battle_SlideInPartyPanel,
    (Callback)Battle_HoldPartyPanel,
    (Callback)func_801EAB64,
};

/* 0x801D0FAC */
BattleMenuRowsPanelSteps g_BattleMenuRowsPanelSteps = {
    (Callback)Battle_DrawMenuRows,
    (Callback)Battle_AnimateMenuRows,
    (Callback)func_801EAB64,
};

/* 0x801D0FB8 */
BattlePanel2Steps D_801D0FB8 = {
    (Callback)func_801EAB64,
    (Callback)func_801E949C,
    (Callback)func_801EAB64,
};

/* 0x801D0FC4 */
BattlePanel3Steps D_801D0FC4 = {
    (Callback)func_801E9530,
    (Callback)func_801E9538,
    (Callback)func_801EAB64,
};

/* 0x801D0FD0 */
Callback g_BattleEnemyPanelSteps[4] = {
    (Callback)Battle_StartEnemyPanel,
    (Callback)Battle_ShowEnemyPanel,
    (Callback)Battle_PlaceEnemyPanel,
    (Callback)func_801EAB64,
};

/* 0x801D0FE0 */
BattleMemberPanelSteps g_BattleMemberPanelSteps = {
    (Callback)Battle_SetPanelGauges,
    (Callback)Battle_ShowMemberPanel,
    (Callback)Battle_MovePanel,
};

/* 0x801D0FEC */
/* D_801D0FEC */
BattlePanelTaskSteps g_BattlePanelTaskForwarders = {
    (BattlePanelTaskCallback)func_801EA254,
    (BattlePanelTaskCallback)func_801EA530,
    (BattlePanelTaskCallback)func_801EA59C,
};

/* 0x801D0FF8 */
BattleEventPanelSteps g_BattleEventPanelSteps = {
    (Callback)Battle_SlideInEventPanel,
    (Callback)func_801EA76C,
    (Callback)Battle_SlideOutEventPanel,
};

/* 0x801D1004 */
BattleMessagePanelSteps g_BattleMessagePanelSteps = {
    (Callback)Battle_WaitMessage,
    (Callback)Battle_SlideInMessagePanel,
    (Callback)Battle_HoldMessagePanel,
    (Callback)Battle_SlideOutMessagePanel,
};
