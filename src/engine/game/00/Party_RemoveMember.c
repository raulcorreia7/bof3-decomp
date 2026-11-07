#include "game_00.h"

/* nonmatching unmeasured: tried frame pad 24 added (65.85%); search-loop limit as signed local gives blez but
 * regresses; prev/cur address order in compaction loop (retail a0=cur, v1=prev via v0-1). */
/* func_801C1ABC */
#ifdef NON_MATCHING
NON_MATCHING void Party_RemoveMember(s32 character_id) {
    s32  slot;
    s32  limit;
    s32  key;
    s32  off;
    s32  code;
    s32  frac;
    u8   value;
    u8*  cur;
    u8*  prev;
    u8*  src;
    u8*  dst;
    u32* wsrc;
    u32* wdst;
    u32* wend;
    /* FAKE: unused frame, 24 bytes. */
    STACK_PADS(u8, 24);

    func_801C1840();
    slot = 0;
    if ((s32)g_PartySize > 0) {
        key   = character_id & BYTE_MASK;
        limit = g_PartySize;
    search1:
        if (g_PartyBattleOrder[slot] == key)
            goto found1;
        slot++;
        if (slot < limit)
            goto search1;
    found1:;
    }
    g_PartyBattleOrder[slot] = 0xFF;
    if (slot < (s32)g_PartySize - 1) {
        cur  = &D_80144F5E[slot];
        prev = cur - 1;
        do {
            if (*prev == GAME_NONE) {
                *prev = *cur;
                *cur  = 0xFF;
            }
            cur++;
            slot++;
            prev++;
        } while (slot < (s32)g_PartySize - 1);
    }
    slot = 0;
    if ((s32)g_PartySize > 0) {
        key   = character_id & BYTE_MASK;
        limit = g_PartySize;
    search2:
        if (g_PartyFieldOrder[slot] == key)
            goto found2;
        slot++;
        if (slot < limit)
            goto search2;
    found2:;
    }
    g_PartyFieldOrder[slot] = 0xFF;
    if ((s32)g_PartySize - 1 > 0) {
        slot = 0;
        off  = 0;
        code = 0x78;
        frac = 0;
        src  = &((u8*)g_BattlePartyBattlers)[BATTLE_PARTY_STRIDE];
        dst  = (u8*)g_BattlePartyBattlers;
        do {
            if ((&D_80144EE2)[code] == GAME_NONE) {
                TASK_SET(dst);
                value                   = (&D_80144EE2)[code + 1];
                (&D_80144EE2)[code + 1] = 0xFF;
                (&D_80144EE2)[code]     = value;
                wsrc                    = (u32*)src;
                wdst                    = (u32*)dst;
                wend                    = (u32*)(src + BATTLE_PARTY_STRIDE);
                do {
                    wdst[0] = wsrc[0];
                    wdst[1] = wsrc[1];
                    wdst[2] = wsrc[2];
                    wdst[3] = wsrc[3];
                    wsrc += 4;
                    wdst += 4;
                } while (wsrc != wend);
                g_Task->unk_05                                   = (u8)slot;
                g_Task->unk_26                                   = (u8)frac;
                g_Task->unk_27                                   = (u8)code;
                g_Task->unk_4B                                   = 0xFF;
                (&g_BattlePartyBattlers[0].character_index)[off] = g_CharSlot[(&D_80145F09)[off]];
            }
            off += BATTLE_PARTY_STRIDE;
            code++;
            frac += 0x50;
            src += BATTLE_PARTY_STRIDE;
            slot++;
            dst += BATTLE_PARTY_STRIDE;
        } while (slot < (s32)g_PartySize - 1);
    }
    ((u8*)g_BattlePartyBattlers)[((s32)g_PartySize - 1) * BATTLE_PARTY_STRIDE] = 0;
    Party_ClearBattlerState(((s32)g_PartySize - 1) & BYTE_MASK);
    if (g_PartySize == 3) {
        if (g_PartyFormation >= 3u)
            g_PartyFormation = 0;
        else
            goto tail;
    } else {
    tail:
        if (g_PartySize == 2)
            g_PartyFormation = 0;
    }
    g_PartySize = (u8)((s32)g_PartySize - 1);
}
#else
INCLUDE_ASM(Party_RemoveMember);
#endif
