#include "battle_03.h"

/* ticks the scratch work's step counter at +0x9; on step 0 it resets the battle bar, clears the +0x80
 * re-arm flag, halves +0x8C, fills a 0x78-stride effect record (Battle_AllocEffect, flags 1 and 6), queues cue
 * 0x206 and, when g_BattleEventFlags is clear, runs the cleanup calls and advances the battle work.
 */
MATCH void func_801E0F0C(void) {
    PartyBattler* spad;
    PartyBattler* spad2;
    PartyBattler* work;
    s32           count;
    s32           offset;
    /* FAKE: retail materializes the bar reset constant in v1. */
    MATCH_REG(s16, one, "v1");
    /* FAKE: retail materializes the +0x124 mask in a3. */
    MATCH_REG(s32, mask, "a3");

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        work         = g_GameState;
        one          = 1;
        mask         = ~4;
        work->chr.hp = one;
        work->chr.status &= ~STATUS_KO;
        work->chr.willpower >>= 1;
        work->turn.damage_flags.value &= mask;
        offset                       = (Battle_AllocEffect(0, 1) & BYTE_MASK) * 0x78;
        spad                         = g_Task;
        *(&D_801EC337 + offset)      = 1;
        *(&D_801EC357 + offset)      = 6;
        spad2                        = g_Task;
        *(u32*)(D_801EC3A4 + offset) = spad;
        Actor_SelectScript((spad2->facing + 4) & BYTE_MASK);
        SND_QueueSelectionFx(0x206);
        if (g_BattleEventFlags == 0) {
            func_801D9484();
            Battle_SetTextPartyName(g_Task->slot);
            func_801DEBC4(0, g_GameState->chr.character_id);
        }
        g_Task->unk_03 = 2;
        func_801DEDE4();
    }
}
