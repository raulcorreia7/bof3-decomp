#include "battle_03.h"

/* Overlay head .data, 0x801D0F20..0x801D1014: the panel, preview and
 * result handler tables the overlay dispatches through. */

/* In-overlay dispatch targets (split assembly units). */
extern void func_801EA254(void), func_801EA530(void);
extern void func_801EA59C(void);

/* 0x801D0F20 */
Effect801D0F20Steps D_801D0F20 = {
    (Callback)func_801E6420,
    (Callback)func_801E64B4,
    (Callback)func_801E65F8,
};

/* 0x801D0F2C */
Effect801D0F2CSteps D_801D0F2C = {
    (Callback)func_801E6990,
    (Callback)func_801E69C0,
    (Callback)func_801E6A54,
};

/* 0x801D0F38 */
Effect801D0F38Steps D_801D0F38 = {
    (Callback)func_801E6B28,
    (Callback)func_801E6BC8,
    (Callback)func_801E6C20,
};

/* 0x801D0F44 */
Effect801D0F44Steps D_801D0F44 = {
    (Callback)func_801E6D28, (Callback)func_801E6E54, (Callback)func_801E6FA0,
    (Callback)func_801E6FB0, (Callback)func_801E71EC,
};

/* 0x801D0F58 */
Effect801D0F58Steps D_801D0F58 = {
    (Callback)func_801E7528, (Callback)func_801E7558, (Callback)func_801E75B0,
    (Callback)func_801E7634, (Callback)func_801E7778,
};

/* 0x801D0F6C */
BattleSavedPreviewFuncs D_801D0F6C = {
    (Callback)func_801E7888, (Callback)func_801E78F0, (Callback)func_801E7948,
    (Callback)func_801E7BA0, (Callback)func_801E8558,
};

/* 0x801D0F80 */
/* D_801D0F80 */
BattlePanelFuncs g_BattlePanelFuncs = {
    (Callback)func_801E90FC, (Callback)func_801E91FC, (Callback)func_801E943C, (Callback)func_801E94D0,
    (Callback)func_801E960C, (Callback)func_801E9B18, (Callback)func_801EA650, (Callback)func_801EA7DC,
};

/* 0x801D0FA0 */
Panel801D0FA0States D_801D0FA0 = {
    (Callback)func_801E915C,
    (Callback)func_801E91CC,
    (Callback)func_801EAB64,
};

/* 0x801D0FAC */
Panel801D0FACStates D_801D0FAC = {
    (Callback)func_801E927C,
    (Callback)func_801E9390,
    (Callback)func_801EAB64,
};

/* 0x801D0FB8 */
Panel801D0FB8States D_801D0FB8 = {
    (Callback)func_801EAB64,
    (Callback)func_801E949C,
    (Callback)func_801EAB64,
};

/* 0x801D0FC4 */
Panel801D0FC4States D_801D0FC4 = {
    (Callback)func_801E9530,
    (Callback)func_801E9538,
    (Callback)func_801EAB64,
};

/* 0x801D0FD0 */
Callback D_801D0FD0[4] = {
    (Callback)func_801E97A8,
    (Callback)func_801E9910,
    (Callback)func_801E99AC,
    (Callback)func_801EAB64,
};

/* 0x801D0FE0 */
Panel801D0FE0States D_801D0FE0 = {
    (Callback)func_801E9CA8,
    (Callback)func_801E9F18,
    (Callback)func_801E9FDC,
};

/* 0x801D0FEC */
/* D_801D0FEC */
BattlePanelTaskForwarders g_BattlePanelTaskForwarders = {
    (BattlePanelForwardFunc)func_801EA254,
    (BattlePanelForwardFunc)func_801EA530,
    (BattlePanelForwardFunc)func_801EA59C,
};

/* 0x801D0FF8 */
Panel801D0FF8States D_801D0FF8 = {
    (Callback)func_801EA728,
    (Callback)func_801EA76C,
    (Callback)func_801EA774,
};

/* 0x801D1004 */
Panel801D1004States D_801D1004 = {
    (Callback)func_801EA848,
    (Callback)func_801EA894,
    (Callback)func_801EA8F4,
    (Callback)func_801EA9FC,
};
