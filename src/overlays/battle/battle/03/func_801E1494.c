#include "battle_03.h"

/* consumes the signed counter at +0x11C against the bar at +0x88: a counter not above the bar re-arms the
 * bar, otherwise it is subtracted within the +0x90 cap (a negative counter queues one cue); then dispatches the
 * +0x120 flag bits and advances the scratch work step.
 */
MATCH void func_801E1494(void) {
    s16           value;
    u16           amount;
    u16           cap;
    PartyBattler* entry;

    PartyBattler* work;
    work  = g_GameState;
    value = (s16)work->hp_change;
    if (work->stats.current_hp <= value) {
        work->stats.status     = STATUS_KO;
        work->stats.current_hp = 0;
        func_801DD858(1);
    } else {
        if (value >= 0) {
            func_801DD858(0);
        } else {
            SND_QueueSelectionFx(0x206);
        }
        entry                   = g_GameState;
        amount                  = entry->stats.current_hp - entry->hp_change;
        cap                     = entry->stats.stats.max_hp;
        entry->stats.current_hp = amount;
        if (cap < amount) {
            entry->stats.current_hp = cap;
        }
    }
    work = g_GameState;
    if (work->unk_120 & 1) {
        func_800AAC88((s16)work->hp_change, g_Task->slot);
        work = g_GameState;
    }
    if (work->unk_120 & 2) {
        func_800AAEBC((s16)work->ap_change, g_Task->slot);
    }
    func_801DEDE4();
    g_Task->unk_03 = g_Task->unk_03 + 1;
}
