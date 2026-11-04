#include "battle_03.h"

MATCH void func_801E10C8(void) {
    PartyBattler* current;
    u32           slot;
    u32           cue;
    u8            count;
    PartyBattler* owner;
    PartyBattler* work;

    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (count == 0) {
        if (g_SpadWork->unk_03 == 3) {
            g_GameState->stats.accessories[0] = ACCESSORY_NOTHING;
        }
        if (g_SpadWork->unk_03 == 5) {
            g_GameState->stats.armor = ARMOR_NOTHING;
            func_801E0B64();
        }
        if (g_SpadWork->unk_03 == 6) {
            g_GameState->stats.accessories[1] = ACCESSORY_NOTHING;
        }
        current = g_GameState;
        current->stats.status &= ~STATUS_KO;
        current->stats.current_hp           = current->stats.max_hp;
        current->stats.current_willpower    = current->stats.willpower;
        slot                                = Battle_AllocEffect(0, 1) & BYTE_MASK;
        owner                               = g_SpadWork;
        g_BattleEffects[slot].unk_07        = 2;
        g_BattleEffects[slot].unk_27        = 6;
        work                                = g_SpadWork;
        g_BattleEffects[slot].work_74.party = owner;
        Actor_SelectScript((work->word_08.byte.facing_08 + 4) & BYTE_MASK);
        SND_QueueSelectionFx(0x206);
        if (g_BattleEventFlags == 0) {
            func_801D9484();
            cue = 0x3B;
            if (g_SpadWork->unk_03 == 5) {
                cue = 0x2E;
            }
            func_801DE560(2, 0, 0, 0x2D, Resource_GetText(cue));
        }
        g_SpadWork->unk_03 = 2;
        func_801DEDE4();
    }
}
