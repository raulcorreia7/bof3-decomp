#include "battle_03.h"

MATCH void func_801E16B4(void) {
    u8            state;
    PartyBattler* work;

    if (EMI_LoaderIsReady() != 0) {
        work  = g_GameState;
        state = work->mode_119;
        if (state == 4) {
            if (!(work->flags_128.value & 2)) {
                if (!(func_801DDF50((u16)work->stats.character_id, D_801463CD) & BYTE_MASK)) {
                    g_Task->unk_09 = 0x1E;
                } else {
                    /* shared exit: the armed step clears the phase byte */
                    goto block_8;
                }
            } else if (((g_DragonForm == state) || ((u32)(g_DragonForm - 7) < 2U)) &&
                       (func_801DDF50((u16)work->stats.character_id, D_801463CD) & BYTE_MASK)) {
                /* shared exit: the armed step clears the phase byte */
                goto block_8;
            }
        } else {
        block_8:
            g_Task->unk_09 = 0;
        }
        if (!(D_801CA71C[g_BattleActionId].mask & 0x800)) {
            work = g_GameState;
            if (work->flags_128.value & 2) {
                g_Task->unk_09 = D_801EB23C[g_DragonForm];
            } else {
                g_Task->unk_09 = s_BattleCharacterStepIds[work->stats.character_id];
            }
            Actor_RequestScript((g_Task->facing + 0x2C) & BYTE_MASK);
            g_Task->step = g_Task->step + 1;
        } else {
            g_Task->mode = g_Task->mode + 1;
        }
        func_801DEE4C();
    }
}
