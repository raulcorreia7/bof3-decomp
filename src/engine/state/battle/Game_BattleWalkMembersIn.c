#include "engine/game/00/game_00.h"

/* func_801BF11C */
MATCH bool Game_BattleWalkMembersIn(void) {
    PartyMember* work;
    s32          i;
    s32          j;
    u8           order;
    s32          clut_offset;
    u16*         dst;
    u16*         src;
    Actor*       actor;
    u16          color;
    s32          palette_offset;

    if (g_Battle.outcome.options & 0x4) {
        return 1;
    }

    g_AreaEncounterPlacement.origin.x.fixed = g_AreaCamera.scroll_x.fixed + (s_CameraScrollDeltas[g_Battle.scroll_dir].dx << 16);
    g_AreaEncounterPlacement.origin.y.fixed = g_AreaCamera.scroll_y.fixed + (s_CameraScrollDeltas[g_Battle.scroll_dir].dy << 16);

    for (i = 0; i < g_Game.party_size; i++) {
        work           = &g_Game.members[i];
        g_Game.current = work;
        SELF_SET(work);
        if (SELF(Actor)->param.unk_0B == 0) {
            if (func_801C29A0(8) & BYTE_MASK) {
                for (order = 0; order < PARTY_SLOT_COUNT; order++) {
                    if (g_PartyBattleOrder[order] == g_Game.current->chr.character_id) {
                        break;
                    }
                }
                g_Game.current->status.field.flags.unsigned_value &= 0xFE;
                SELF(Actor)->draw_layer       = g_AreaDrawMode;
                SELF(Actor)->pos.x            = g_AreaEncounterPlacement.party[order].x;
                SELF(Actor)->pos.y            = g_AreaEncounterPlacement.party[order].y;
                COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
                SELF(Actor)->unk_48           = 0;
                SELF(Actor)->param.unk_0B     = 1;
            }
        } else if (SELF(Actor)->param.unk_0B == 1) {
            if (func_801C2894(8) & BYTE_MASK) {
                actor = SELF(Actor);
                for (j = 0; j < 32; j++) {
                    clut_offset    = actor->unk_05 << 6;
                    dst            = (u16*)(GAME_PALETTE_MIRROR + clut_offset);
                    src            = (u16*)(GAME_PALETTE_STAGE + clut_offset);
                    palette_offset = j << 1;
                    color          = MEM(u16, (u32)src + palette_offset + 0xC0);
                    palette_offset += (s32)dst;
                    MEM(u16, palette_offset) = color;
                }
                g_GfxPalettePending = 1;
                SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                SELF(Actor)->param.unk_0B = 0;
                ACTOR_CLEAR_TINT();
                SELF(Actor)->tint.bytes.flags = 0;
                SELF(Actor)->param.unk_0B     = 2;
            }
        }
        Script_AnimStepLoop();
    }

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].param.unk_0B != 2) {
            return 0;
        }
    }

    return 1;
}
