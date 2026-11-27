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
    s32          leader_x;
    s32          leader_y;
    s16          rise;
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
            SELF_SET(member);
            g_GameState = member;
            Party_MemberLoadSprite(member->chr.character_id, i & BYTE_MASK);
            g_GameState->status.field.flags.unsigned_value = saved;
            if (g_GameState->status.field.flags.unsigned_value & 1) {
                SELF(PartyMember)->unk_29 = 4;
            }
            g_GameState->chr             = g_Characters[g_CharSlot[g_GameState->chr.character_id]];
            g_GameState->character_index = g_CharSlot[g_GameState->chr.character_id];
            g_PartyFieldOrder[i]         = g_GameState->chr.character_id;
            if (i != 0) {
                Actor_SetSemiTransparent();
                SELF(PartyMember)->header.flags &= 0xBF;
                SELF(PartyMember)->unk_5C = 1;
                SELF(PartyMember)->facing = g_Game.members[0].facing ^ 4;
            }
            if (!(g_Game.members[0].status.field.flags.unsigned_value & 1) && i != 0) {
                index  = (i - 1) * 2 + SELF(PartyMember)->facing * 4;
                ok     = func_801B1B2C(g_Game.members[0].pos.x.fixed + (s_EntityPlacementOffsets[index] << 15), g_Game.members[0].pos.y.fixed + (s_EntityPlacementOffsets[index + 1] << 15),
                                       SELF(PartyMember)->facing, SELF(PartyMember)->speed);
                placed = (ok & BYTE_MASK) ? func_801B1C18(((s32*)&D_1F800008)[0], ((s32*)&D_1F800008)[1], SELF(PartyMember)->speed) : 0;
                if ((ok & BYTE_MASK) && (placed & BYTE_MASK)) {
                    goto found;
                }
                func_801B1B2C(D_80145EC4, D_80145EC8, SELF(PartyMember)->facing, SELF(PartyMember)->speed);
            } else {
                func_801B1B2C(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, SELF(PartyMember)->facing, SELF(PartyMember)->speed);
            }
        found:
            SELF(PartyMember)->pos.x.fixed        = ((s32*)&D_1F800008)[0];
            SELF(PartyMember)->pos.y.fixed        = ((s32*)&D_1F800008)[1];
            SELF(PartyMember)->pos.z.part.integer = Area_HeightRead(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed);
            Script_Select(SELF(PartyMember)->facing);
        }
    }
    SELF_SET(g_Game.members);
    g_GameState       = g_Game.members;
    g_AreaCameraSpeed = 0x20;
    px                = &g_AreaScrollTargetX;
    py                = &g_AreaScrollTargetY;
    leader_x          = g_Game.members[0].pos.x.fixed;
    leader_y          = g_Game.members[0].pos.y.fixed;
    dx                = abs(*px - leader_x);
    dy                = abs(*py - leader_y);
    *px               = leader_x;
    *py               = leader_y;
    if (dx < dy) {
        dx = dy;
    }
    divisor = ((u32)dx >> 13) & BYTE_MASK;
    rise    = g_Game.members[0].pos.z.part.integer - g_AreaCameraHeight;
    if (divisor != 0) {
        g_AreaCameraHeightDelta = rise / divisor;
    } else {
        g_AreaCameraHeightDelta = 0;
    }
    SELF(PartyMember)->unk_09 = 4;
    SELF(PartyMember)->header.step++;
}
#else
INCLUDE_ASM(func_801B21E8);
#endif
