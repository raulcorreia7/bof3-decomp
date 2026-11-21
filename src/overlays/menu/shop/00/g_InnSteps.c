#include "shop_00.h"

Callback g_InnSteps[INN_STEP_COUNT] = {
    func_801D39F8, Menu_RunInnMenu, Menu_RunInnRest, SAVE_DispatchState, func_801D60B0,
};

Callback g_InnMenuSteps[INN_MENU_STATE_COUNT] = {
    func_801D3AE4, func_801D3B98, func_801D3C9C, func_801D3D84, func_801D3FD4, func_801D408C,
};

Callback g_InnRestSteps[INN_REST_STATE_COUNT] = {
    func_801D41EC, func_801D430C, func_801D43A4, func_801D43F0, func_801D446C, func_801D456C, func_801D4614,
};

Callback g_SaveSteps[SAVE_STATE_COUNT] = {
    func_801D46E0, func_801D472C, func_801D47AC, func_801D4970, func_801D4A3C, func_801D4BBC, func_801D4CF0, func_801D4DB4, func_801D4E74, func_801D50C0, func_801D51B8,
    func_801D5390, func_801D543C, func_801D5790, func_801D5894, func_801D5AD0, func_801D5BB0, func_801D5CB0, func_801D5D98, func_801D5E88, func_801D6018,
};

Callback g_ShopStep10Steps[SHOP_STEP10_COUNT] = {
    func_801D61C0, func_801D62DC, func_801D65A0, func_801D65EC, func_801D6668, func_801D66AC, func_801D66C8,
};

s32 D_801E537C[1] = {0x003D0000};
s32 D_801E5380[1] = {0x000E0000};
