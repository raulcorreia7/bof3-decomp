#include "game_00.h"

/* nonmatching: the last party scan is 4 bytes short; retail copies g_PartySize into a0 (blez v0, move a0,v0) and hoists the
 * 2 into a1. First difference 0x801BF148, the epilogue jump target. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801BF11C(void) {
    u8*  work;
    s32  i;
    s32  j;
    u8   order;
    s32  bank;
    u16* dst;
    u16* src;

    if (g_BattleOptions & 4) {
        return 1;
    }
    g_EncounterOriginX = g_AreaScrollTargetX + (s_CameraScrollDeltas[g_BattleScrollDir].dx << 16);
    g_EncounterOriginY = g_AreaScrollTargetY + (s_CameraScrollDeltas[g_BattleScrollDir].dy << 16);
    for (i = 0; i < g_PartySize; i++) {
        work        = (u8*)g_BattlePartyBattlers + i * BATTLE_PARTY_STRIDE;
        g_GameState = (GameState*)work;
        TASK_SET(work);
        if (g_Task->param.unk_0B == 0) {
            if (func_801C29A0(8) & BYTE_MASK) {
                for (order = 0; order < 3; order++) {
                    if (g_PartyBattleOrder[order] == g_GameState->leader_id) {
                        break;
                    }
                }
                g_GameState->flags_12C.u8_value &= 0xFE;
                g_Task->unk_29           = g_AreaDrawMode;
                g_Task->pos.x            = g_EncounterParty[order].x;
                g_Task->pos.y            = g_EncounterParty[order].y;
                COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
                g_Task->unk_48           = 0;
                g_Task->param.unk_0B     = 1;
            }
        } else if (g_Task->param.unk_0B == 1) {
            if (func_801C2894(8) & BYTE_MASK) {
                for (j = 0; j < 0x20; j++) {
                    bank   = g_Task->unk_05 << 6;
                    dst    = MEM_PTR(u16, 0x80039600u + bank);
                    src    = MEM_PTR(u16, 0x80035600u + bank);
                    dst[j] = src[j + 0x60];
                }
                g_GfxPalettePending = 1;
                g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                g_Task->param.unk_0B = 0;
                ACTOR_CLEAR_TINT();
                g_Task->tint.bytes.flags = 0;
                g_Task->param.unk_0B     = 2;
            }
        }
        func_8014D978();
    }
    for (i = 0; i < g_PartySize; i++) {
        if ((&D_80145E9B)[i * BATTLE_PARTY_STRIDE] != 2) {
            return 0;
        }
    }
    return 1;
}
#else
INCLUDE_ASM(func_801BF11C);
#endif
