#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801B21E8(void) {
    PartyMember* member;
    s32          i;
    s32          ok;
    s32          placed;
    s32          index;
    s32          dx;
    s32          dy;
    s32          diff;
    s32          divisor;
    u8           saved;
    s32*         px;
    s32*         py;

    saved = g_GameState->status.field.flags.unsigned_value;
    if (g_Game.members[1].header.mode == 3) {
        Party_BattlersSwapRows(0, 1, 1);
        if (g_PartySize == 3 && g_Game.members[2].header.mode == 3) {
            Party_BattlersSwapRows(1, 2, 1);
        }
    } else if (g_PartySize == 3 && g_Game.members[2].header.mode == 3) {
        Party_BattlersSwapRows(0, 2, 1);
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].header.mode == 3) {
            member = &g_Game.members[i];
            TASK_SET(member);
            g_GameState = member;
            Party_MemberLoadSprite(member->chr.character_id, i & BYTE_MASK);
            g_GameState->status.field.flags.unsigned_value = saved;
            if (g_GameState->status.field.flags.unsigned_value & 1) {
                TASK(PartyMember)->unk_29 = 4;
            }
            g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
            g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];
            g_PartyFieldOrder[i]         = g_GameState->chr.character_id;
            if (i != 0) {
                Actor_SetSemiTransparent();
                TASK(PartyMember)->header.flags &= 0xBF;
                TASK(PartyMember)->unk_5C = 1;
                TASK(PartyMember)->facing = g_Game.members[0].facing ^ 4;
            }
            if (!(g_Game.members[0].status.field.flags.unsigned_value & 1) && i != 0) {
                index  = (i - 1) * 2 + TASK(PartyMember)->facing * 4;
                ok     = func_801B1B2C(g_Game.members[0].pos.x.fixed + (s_EntityPlacementOffsets[index] << 15), g_Game.members[0].pos.y.fixed + (s_EntityPlacementOffsets[index + 1] << 15), TASK(PartyMember)->facing,
                                       TASK(PartyMember)->speed);
                placed = (ok & BYTE_MASK) ? func_801B1C18(((s32*)&D_1F800008)[0], ((s32*)&D_1F800008)[1], TASK(PartyMember)->speed) : 0;
                if ((ok & BYTE_MASK) && (placed & BYTE_MASK)) {
                    goto found;
                }
                func_801B1B2C(D_80145EC4, D_80145EC8, TASK(PartyMember)->facing, TASK(PartyMember)->speed);
            } else {
                func_801B1B2C(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, TASK(PartyMember)->facing, TASK(PartyMember)->speed);
            }
        found:
            TASK(PartyMember)->pos.x.fixed        = ((s32*)&D_1F800008)[0];
            TASK(PartyMember)->pos.y.fixed        = ((s32*)&D_1F800008)[1];
            TASK(PartyMember)->pos.z.part.integer = Area_HeightRead(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed);
            Script_Select(TASK(PartyMember)->facing);
        }
    }
    TASK_SET(g_Game.members);
    g_GameState       = g_Game.members;
    g_AreaCameraSpeed = 0x20;
    px                = &g_AreaScrollTargetX;
    py                = &g_AreaScrollTargetY;
    diff              = *px - g_Game.members[0].pos.x.fixed;
    dx                = diff;
    if (diff < 0) {
        dx = -dx;
    }
    diff = *py - g_Game.members[0].pos.y.fixed;
    dy   = diff;
    if (diff < 0) {
        dy = -dy;
    }
    *px = g_Game.members[0].pos.x.fixed;
    *py = g_Game.members[0].pos.y.fixed;
    if (dx < dy) {
        dx = dy;
    }
    divisor = ((u32)dx >> 13) & BYTE_MASK;
    if (divisor != 0) {
        g_AreaCameraHeightDelta = (s16)((u16)g_Game.members[0].pos.z.part.integer - g_AreaCameraHeight) / divisor;
    } else {
        g_AreaCameraHeightDelta = 0;
    }
    TASK(PartyMember)->unk_09 = 4;
    TASK(PartyMember)->header.step++;
}
#else
INCLUDE_ASM(func_801B21E8);
#endif
