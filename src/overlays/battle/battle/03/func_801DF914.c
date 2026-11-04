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
    if ((current->flags_128.value & 2) != 0) {
        selector                          = &g_DragonForm;
        g_SpadWork->word_08.byte.unk_09   = *(u8*)((u8*)&D_801EB198 + *selector);
        g_SpadWork->word_08.byte.timer_0A = *(u8*)((u8*)&D_801EB198 + *selector);
    } else {
        g_SpadWork->word_08.byte.unk_09   = *(u8*)((u8*)&s_BattleCharacterSprites + current->stats.character_id);
        g_SpadWork->word_08.byte.timer_0A = *(u8*)((u8*)&s_BattleCharacterSprites + g_GameState->stats.character_id);
    }
    Actor_RequestScript((g_SpadWork->word_08.byte.unk_08 + 0xC) & BYTE_MASK);
    func_801DEDE4();
    work          = g_SpadWork;
    work->step_01 = work->step_01 + 1;
}
