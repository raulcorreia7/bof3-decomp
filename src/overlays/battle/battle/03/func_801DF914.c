#include "battle_03.h"

/* loads the active work area's two sprite bytes from either the queued
 * battler table or the current battler table, queues the palette step and
 * advances the area's phase.
 */
MATCH void func_801DF914(void) {
    PartyBattler* current;
    PartyBattler* work;
    u8*           selector;

    current = g_GameState;
    if ((current->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) != 0) {
        selector       = &g_DragonForm;
        g_Task->unk_09 = *(u8*)((u8*)&D_801EB198 + *selector);
        g_Task->timer  = *(u8*)((u8*)&D_801EB198 + *selector);
    } else {
        g_Task->unk_09 = *(u8*)((u8*)&s_BattleCharacterSprites + current->chr.character_id);
        g_Task->timer  = *(u8*)((u8*)&s_BattleCharacterSprites + g_GameState->chr.character_id);
    }
    Actor_RequestScript((g_Task->facing + 0xC) & BYTE_MASK);
    func_801DEDE4();
    work              = g_Task;
    work->header.mode = work->header.mode + 1;
}
