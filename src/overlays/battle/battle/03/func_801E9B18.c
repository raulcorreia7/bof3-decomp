#include "battle_03.h"

/* dispatches one of three panel-task handlers by battle state byte +0x03, draws the selected battler row's
 * two bars and sets or clears its 0x2000 bit from the gauge fraction.
 */
MATCH void func_801E9B18(void) {
    BattleHandlerTable3 handlers;
    u16                 flags;
    u32                 offset;
    u32                 slot;
    u8*                 row;

    handlers = D_801D0FE0;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
    row = D_80145F04 + BATTLE_PANEL_TASK->cell_0A.slot * BATTLE_PARTY_STRIDE;
    func_801EA1E0((s32)(((u8*)g_MenuPanelTaskCurrent) + 0xB), (s32)(row + 0x1C),
                  (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x1C), (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x14),
                  (s32)(row + 0x14), (s32)(((u8*)g_MenuPanelTaskCurrent) + 0xD),
                  (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x18), ((u8*)g_MenuPanelTaskCurrent) + 0x8);
    row = D_80145F04 + BATTLE_PANEL_TASK->cell_0A.slot * BATTLE_PARTY_STRIDE;
    func_801EA1E0((s32)(((u8*)g_MenuPanelTaskCurrent) + 0xC), (s32)(row + 0x1E),
                  (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x1E), (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x16),
                  (s32)(row + 0x16), (s32)(((u8*)g_MenuPanelTaskCurrent) + 0xE),
                  (s32)(((u8*)g_MenuPanelTaskCurrent) + 0x1A), ((u8*)g_MenuPanelTaskCurrent) + 0x9);
    slot   = BATTLE_PANEL_TASK->cell_0A.slot;
    offset = slot * BATTLE_PARTY_STRIDE;
    if (g_BattlePartyBattlers[slot].stats.current_hp < (u32)(g_BattlePartyBattlers[slot].stats.max_hp >> 2)) {
        flags = *(u16*)(D_80145F10 + offset) | 0x2000;
    } else {
        flags = *(u16*)(D_80145F10 + offset) & 0xDFFF;
    }
    *(u16*)(D_80145F10 + offset) = flags;
}
