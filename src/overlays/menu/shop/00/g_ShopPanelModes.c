#include "shop_00.h"

// clang-format off
Callback g_ShopPanelModes[SHOP_MODE_COUNT] = {
    Menu_MessagePanel,
    Menu_ZennyPanel,
    Menu_CommandsPanel,
    UI_CursorDrawPanel,
    Menu_CursorFramePanel,
    Menu_EquipStatPanel,
    Menu_EquipmentPanel,
    Menu_ItemsPanel,
    func_801E36F8,
    Menu_InventoryPanel,
    func_801E3B7C,
    func_801E3BA4,
    func_801E3CF8,
    Menu_CharacterPanel,
    func_801E3F34,
    func_801E4224,
    func_801E4338,
    func_801E440C,
    func_801E44E0,
};
