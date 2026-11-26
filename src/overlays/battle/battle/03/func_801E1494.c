#include "battle_03.h"

/* consumes the signed counter at +0x11C against the bar at +0x88: a counter not above the bar re-arms the
 * bar, otherwise it is subtracted within the +0x90 cap (a negative counter queues one cue); then dispatches the
 * +0x120 flag bits and advances the scratch work step.
 */
MATCH void func_801E1494(void) {
    s16          value;
    u16          amount;
    u16          cap;
    PartyMember* entry;

    PartyMember* work;
    work  = g_Game.current;
    value = work->u.turn.hp_change;
    if (work->chr.hp <= value) {
        work->chr.status = STATUS_KO;
        work->chr.hp     = 0;
        Battle_PlayEffectSE(1);
    } else {
        if (value >= 0) {
            Battle_PlayEffectSE(0);
        } else {
            SND_SEQueueSelection(0x206);
        }
        entry         = g_Game.current;
        amount        = entry->chr.hp - entry->u.turn.hp_change;
        cap           = entry->chr.stats.max_hp;
        entry->chr.hp = amount;
        if (cap < amount) {
            entry->chr.hp = cap;
        }
    }
    work = g_GameState;
    if (work->u.turn.target_flags & BATTLE_HIT_HP) {
        Battle_QueueAction(work->u.turn.hp_change, SELF(PartyMember)->slot);
        work = g_Game.current;
    }
    if (work->u.turn.target_flags & BATTLE_HIT_AP) {
        func_800AAEBC(work->u.turn.ap_change, SELF(PartyMember)->slot);
    }
    func_801DEDE4();
    SELF(PartyMember)->unk_03 = SELF(PartyMember)->unk_03 + 1;
}
