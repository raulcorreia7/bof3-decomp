#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801B21E8(void) {
    s16*   val0;
    s32    cnt;
    s32    tmp0;
    s32    tmp1;
    s32    tmp2;
    s32    tmp3;
    s32    val1;
    s32    val2;
    s32    val3;
    s32    val4;
    s32    val5;
    s32    val6;
    s32    val7;
    s32    val8;
    s32    val9;
    s32    val10;
    Actor* tmp4;
    u32*   tmp5;
    u32*   tmp6;
    Actor* tmp7;
    Actor* tmp8;
    Actor* tmp9;
    u8*    val11;
    u8*    val12;
    u8*    val13;
    u8     tmp10;
    u8     val14;
    void*  tmp11;
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    val3  = 3;
    val14 = g_GameState->status.field.flags.unsigned_value;
    if (g_Game.members[1].header.mode == 3) {
        Party_BattlersSwapRows(0, 1, 1);
        if (g_PartySize == 3) {
            if (g_Game.members[2].header.mode == 3) {
                Party_BattlersSwapRows(1, 2, 1);
            }
        }
    } else if (g_PartySize == 3) {
        if (g_Game.members[2].header.mode == g_PartySize) {
            Party_BattlersSwapRows(0, 2, 1);
        }
    }
    val4 = 0;
    cnt  = g_PartySize;
    if (cnt > 0) {
        val13 = &g_Game.members[0].status.field.flags.value;
        val13 = &g_Game.members[0].status.field.flags.value;
        val0  = &g_ScratchPad.cells.halves[4];
        val0  = &g_ScratchPad.cells.halves[4];
        val6  = -2;
        val5  = 0;
        do {
            if (D_80145E91[val5] == 3) {
                tmp5        = (u8*)g_Game.members + val5;
                g_Task      = tmp5;
                g_GameState = tmp5;
                Party_MemberLoadSprite(FIELD(u8, tmp5, 0x79u), val4 & BYTE_MASK);
                g_GameState->status.field.flags.unsigned_value = val14;
                if (g_GameState->status.field.flags.unsigned_value & 1) {
                    FIELD(s8, g_Task, 0x29u) = 4;
                }
                val11 = (u8*)g_Characters;
                val12 = (u8*)g_GameState + 0x74;
                val11 += g_CharSlot[g_GameState->chr.character_id] * 0xA4;
                tmp11 = val11 + 0xA0;
                do {
                    FIELD(s32, val12, 0)    = FIELD(s32, val11, 0);
                    FIELD(s32, val12, 0x4u) = FIELD(s32, val11, 0x4u);
                    FIELD(s32, val12, 0x8u) = FIELD(s32, val11, 0x8u);
                    FIELD(s32, val12, 0xCu) = FIELD(s32, val11, 0xCu);
                    val11 += 0x10;
                    val12 += 0x10;
                } while (val11 != tmp11);
                *val12                       = *val11;
                g_GameState->character_index = (u8)g_CharSlot[g_GameState->chr.character_id];
                g_PartyFieldOrder[val4]      = g_GameState->chr.character_id;
                if (val4 != 0) {
                    Actor_SetSemiTransparent();
                    tmp6                          = g_Task;
                    *(u8*)(tmp6)                  = (u8)(*(u8*)(tmp6) & 0xBF);
                    TASK(Actor)->tint.steps.flags = 1;
                    TASK(Actor)->direction        = (u8)(g_Game.members[0].facing ^ 4);
                }
                if (!(*val13 & 1) && (val4 != 0)) {
                    tmp4  = g_Task;
                    tmp10 = tmp4->direction;
                    tmp1  = val6 + (tmp10 * 4);
                    val3  = func_801B1B2C(FIELD(s32, val13, -0xF8) + (*(s32*)(s_EntityPlacementOffsets + tmp1 * 4) << 0xF), FIELD(s32, val13, -0xF4) + (*(s32*)(D_801CD08D + tmp1 * 4) << 0xF),
                                          (s32)tmp10, tmp4->voice_flags.scene_flag);
                    val8  = val3 & BYTE_MASK;
                    val9  = 0;
                    if (val8 != 0) {
                        val9 = func_801B1C18(*(s32*)val0, FIELD(s32, val0, 0x4u), TASK(Actor)->voice_flags.scene_flag);
                        val8 = val3 & BYTE_MASK;
                    }
                    if ((val8 == 0) || !(val9 & BYTE_MASK)) {
                        val1 = g_Game.members[0].pos.x.fixed;
                        val2 = g_Game.members[0].pos.y.fixed;
                        goto block_26; /* retail branch */
                    }
                } else {
                    val1 = FIELD(s32, val13, -0xF8);
                    val2 = FIELD(s32, val13, -0xF4);
                block_26:
                    func_801B1B2C(val1, val2, TASK(Actor)->direction, TASK(Actor)->voice_flags.scene_flag);
                }
                tmp7                     = g_Task;
                tmp7->pos.x.fixed        = (s32) * (s32*)(&g_ScratchPad.cells.halves[4]);
                tmp7->pos.y.fixed        = FIELD(s32, val0, 0x4u);
                tmp8                     = g_Task;
                tmp8->pos.z.part.integer = Area_HeightRead(tmp7->pos.x.fixed, FIELD(s32, val0, 0x4u));
                Script_Select(tmp8->direction);
            }
            val6 += 2;
            val4 += 1;
            val5 += BATTLE_PARTY_STRIDE;
        } while (val4 < (s32)g_PartySize);
    }
    TASK_SET(g_Game.members);
    g_GameState       = g_Game.members;
    g_AreaCameraSpeed = 0x20;
    tmp3              = g_AreaScrollTargetX - g_Game.members[0].pos.x.fixed;
    val7              = tmp3;
    if (tmp3 < 0) {
        val7 = -val7;
    }
    tmp2  = g_AreaScrollTargetY - g_Game.members[0].pos.y.fixed;
    val10 = tmp2;
    if (tmp2 < 0) {
        val10 = -val10;
    }
    g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
    g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
    val7                = MAX(val7, val10);
    tmp0                = ((u32)val7 >> 0xD) & BYTE_MASK;
    if (tmp0 != 0) {
        g_AreaCameraHeightDelta = (s16)((s16)((u16)g_Game.members[0].pos.z.part.integer - g_AreaCameraHeight) / tmp0);
    } else {
        g_AreaCameraHeightDelta = 0;
    }
    FIELD(s8, g_Task, 0x9u) = 4;
    tmp9                    = g_Task;
    tmp9->header.step       = (u8)(tmp9->header.step + 1);
}
#else
INCLUDE_ASM(func_801B21E8);
#endif
