#include "battle_03.h"

/* Starts the next queued battler: walks the live battler cursors, arms the
 * first one whose row is idle and queues its action step.
 */
/* nonmatching unmeasured: tried the cursor walk with a byte-cursor alias for the body writes and a halfword view for
 * the g_InputHeld clear, which reproduces retail's reload and pre-branch test (80.81%). residual: our body is 16 bytes
 * too long, the flag stores at -0x24/-0x48 rematerialize absolute, and the tail writes the state bytes absolutely where
 * retail holds &g_BattleRowCursor in a0 and reaches -4/-5. resume: a source shape that keeps one flag base live across
 * the delay slot. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D1D10(void) {
    s8*          cursor;
    s8*          slot;
    volatile u8* flag;
    u8           id;
    u32          index;
    if (EMI_LoaderIsReady() != 0) {
        cursor = &g_BattleCommandCount;
        if (*cursor == 0)
            g_InputHeld = 0;
        if (*cursor < 3) {
            slot = cursor;
            for (; *slot < BATTLE_PARTY_SLOT_COUNT; ((u8*)slot)[0] += 1) {
                id    = D_801462F6[*slot];
                index = id & BYTE_MASK;
                if (index != GAME_NONE) {
                    ((u8*)slot)[-0x15] = id;
                    if (!HAS_STATUS(g_BattlePartyBattlers[index], STATUS_CONFUSED) &&
                        !(g_BattlePartyBattlers[index].turn.action_flags.volatile_value & 0x14001)) {
                        g_BattleMessageSlot = (u8*)&g_BattlePartyBattlers[index];
                        D_801EB4D8          = &g_BattlePartyBattlers[index].turn.command;
                        BattleStageMessageResource((s32)&g_BattlePartyBattlers[index]);
                        ((u8*)slot)[-0x22] += 1;
                        flag        = &g_BattleMessageState;
                        *flag       = 1;
                        flag[-0x24] = 1;
                        flag[-0x48] = 1;
                        return;
                    }
                }
            }
        }
        g_BattleRowCursor  = 0;
        g_BattlePanelEntry = 0;
        D_801463B0         = 0xE;
        g_BattleStep       = 0;
        g_BattleMode += 1;
    }
}
#else
INCLUDE_ASM(func_801D1D10);
#endif
