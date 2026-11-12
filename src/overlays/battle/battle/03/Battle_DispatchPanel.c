#include "battle_03.h"

/* dispatches one of three panel-task handlers by battle state byte +0x03, draws the selected battler row's
 * two bars and sets or clears its 0x2000 bit from the gauge fraction.
 */
/* func_801E9B18 */
MATCH void Battle_DispatchPanel(void) {
    BattlePanel5States handlers;
    u16                flags;
    u32                offset;
    u32                slot;
    u8*                row;

    handlers = D_801D0FE0;
    handlers.states[BATTLE_PANEL_TASK->state]();
    row = D_80145F04 + BATTLE_PANEL_TASK->cell_0A.slot * BATTLE_PARTY_STRIDE;
    func_801EA1E0((((u8*)g_MenuCurrentPanel) + 0xB), (row + 0x1C), (((u8*)g_MenuCurrentPanel) + 0x1C), (((u8*)g_MenuCurrentPanel) + 0x14), (row + 0x14), (((u8*)g_MenuCurrentPanel) + 0xD),
                  (((u8*)g_MenuCurrentPanel) + 0x18), ((u8*)g_MenuCurrentPanel) + 0x8);
    row = D_80145F04 + BATTLE_PANEL_TASK->cell_0A.slot * BATTLE_PARTY_STRIDE;
    func_801EA1E0((((u8*)g_MenuCurrentPanel) + 0xC), (row + 0x1E), (((u8*)g_MenuCurrentPanel) + 0x1E), (((u8*)g_MenuCurrentPanel) + 0x16), (row + 0x16), (((u8*)g_MenuCurrentPanel) + 0xE),
                  (((u8*)g_MenuCurrentPanel) + 0x1A), ((u8*)g_MenuCurrentPanel) + 0x9);
    /* The chr.status view changes the schedule and size, so the flags keep the D_80145F10 address view. */
    slot   = BATTLE_PANEL_TASK->cell_0A.slot;
    offset = slot * BATTLE_PARTY_STRIDE;
    if (g_Game.members[slot].chr.hp < (g_Game.members[slot].chr.stats.max_hp >> 2)) {
        flags = *(u16*)(D_80145F10 + offset) | 0x2000;
    } else {
        flags = *(u16*)(D_80145F10 + offset) & 0xDFFF;
    }
    *(u16*)(D_80145F10 + offset) = flags;
}
