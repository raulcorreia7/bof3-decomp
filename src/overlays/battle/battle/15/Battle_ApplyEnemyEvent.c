#include "battle_15.h"

/* applies one battle event packet to the current enemy work row,
 * dispatches the per-kind record updates, then copies the packet's eight tail
 * bytes.
 */
/* func_8009C994 */
MATCH void Battle_ApplyEnemyEvent(EnemyBattler* work_arg, BattleEventPacket* event) {
    EnemyBattler* work;
    u8*           saved;
    u32           mask;
    s32           factor;
    s32           scaled;
    u8            i;

    work = (EnemyBattler*)(void*)work_arg;
    switch (event->effect_kind) {
        case 0:
            break;
        case 1:
            work->event_flags = event->selector;
            break;
        case 2:
            saved = TASK_BYTES;
            TASK_SET(work);
            func_800A36F0(work->slot, 0xFFFF);
            func_800A31E0(((EnemyBattler*)(void*)g_Task)->slot, *(u8*)&((EnemyBattler*)(void*)work)->status | event->selector);
            TASK_SET(saved);
            break;
        case 3:
            mask = event->selector;
            for (i = 0; i < 8; i++) {
                if (mask & 0x80) {
                    Battle_ScaleEnemyStat((u8*)work, i, event->value);
                }
                mask <<= 1;
            }
            break;
        case 4:
            mask = event->selector;
            for (i = 0; i < 8; i++) {
                if (mask & 0x80) {
                    func_8009CF80((u8*)work, i, event->value);
                }
                mask <<= 1;
            }
            break;
        case 5:
            if (event->selector & 0x2) {
                work->drops[0].rate = event->value;
            }
            if (event->selector & 0x1) {
                work->drops[1].rate = event->value;
            }
            break;
        case 6:
            if (event->selector & 0x2) {
                factor    = event->value * 100;
                scaled    = work->exp * factor / 1000;
                work->exp = (u32)scaled > 0xFFFF ? 0xFFFF : scaled;
            }
            if (event->selector & 0x1) {
                factor      = event->value * 100;
                scaled      = work->zenny * factor / 1000;
                work->zenny = (u32)scaled > 0xFFFF ? 0xFFFF : scaled;
            }
            break;
        case 7:
            D_801463D7 = event->selector;
            break;
    }
    work->choice_ai = event->unk_04;
    for (i = 0; i < ENEMY_SKILL_COUNT; i++) {
        work->skills[i] = event->unk_08[i];
    }
    Battle_RescaleStats(work->slot);
    if (work->hp != 0 && event->panel_id != 0 && D_801EB5A8 < 8) {
        D_801ED9B0[D_801EB5A8].owner_index = work->slot - 3;
        D_801ED9B0[D_801EB5A8].panel_id    = event->panel_id;
        D_801EB5A8++;
    }
}
