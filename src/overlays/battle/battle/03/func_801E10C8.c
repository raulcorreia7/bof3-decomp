#include "battle_03.h"

MATCH void func_801E10C8(void) {
    PartyMember* current;
    u32          slot;
    u32          cue;
    u8           count;
    PartyMember* owner;
    PartyMember* work;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        if (SELF(PartyMember)->unk_03 == 3) {
            g_Game.current->chr.equip.accessories[0] = ACCESSORY_NOTHING;
        }
        if (SELF(PartyMember)->unk_03 == 5) {
            g_Game.current->chr.equip.armor = ARMOR_NOTHING;
            func_801E0B64();
        }
        if (SELF(PartyMember)->unk_03 == 6) {
            g_Game.current->chr.equip.accessories[1] = ACCESSORY_NOTHING;
        }
        current = g_Game.current;
        current->chr.status &= ~STATUS_KO;
        current->chr.hp                    = current->chr.stats.max_hp;
        current->chr.willpower             = current->chr.stats.willpower;
        slot                               = Battle_AllocEffect(0, 1) & BYTE_MASK;
        owner                              = SELF(PartyMember);
        g_BattleEffects[slot].unk_07       = 2;
        g_BattleEffects[slot].unk_27       = 6;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].target.party = owner;
        Script_Select((work->facing + 4) & BYTE_MASK);
        SND_SEQueueSelection(0x206);
        if (g_Battle.outcome.event_flags == 0) {
            Battle_OpenPanel();
            cue = 0x3B;
            if (SELF(PartyMember)->unk_03 == 5) {
                cue = 0x2E;
            }
            Battle_QueueEvent(2, 0, 0, 45, UI_MessageGetText(cue));
        }
        SELF(PartyMember)->unk_03 = 2;
        func_801DEDE4();
    }
}
