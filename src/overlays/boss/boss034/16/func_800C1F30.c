#include "boss034_16.h"

MATCH u8 func_800C1F30(u32 mode) {
    switch (mode & BYTE_MASK) {
        case BOSS_EVENT_RESTART_BEGIN:
        case BOSS_EVENT_TURN_END:
        case BOSS_EVENT_TICK:
        case BOSS_EVENT_EFFECTS_LOADED:
            break;
        case BOSS_EVENT_ACTION_START:
            if (!(g_Battle.boss_flags & BOSS034_FLAG_WERETIGER_GRANTED) && (g_Battle.boss_flags & BOSS034_FLAG_FIRST_TURN_INSERTED) && (g_Battle.active_battler == D_800C2778)) {
                g_Battle.action_type     = BATTLE_ACTION_ABILITY;
                g_Battle.action->type    = BATTLE_ACTION_ABILITY;
                g_Battle.action->unk_02  = ABILITY_WERETIGER;
                g_Battle.action_id       = ABILITY_WERETIGER;
                g_Battle.target_selector = D_800C2778;
                g_Battle.boss_flags |= BOSS034_FLAG_WERETIGER_GRANTED;
                Char_AddAbility(ABILITY_WERETIGER, 4, 0, 0);
                Char_AddAbility(ABILITY_WERETIGER, D_800C2778, 0, 1);
            }
            break;
        case BOSS_EVENT_RESTART_END:
            if (!(g_Battle.state & BATTLE_STATE_RELOAD_PARTY) && !(g_Battle.boss_flags & BOSS034_FLAG_FIRST_TURN_INSERTED) && !(g_Game.members[D_800C2778].chr.status & STATUS_LOW_HP)) {
                g_Battle.boss_flags |= BOSS034_FLAG_FIRST_TURN_INSERTED;
                Battle_InsertTurnFirst(D_800C2778);
            }
            break;
    }
    return 0;
}
