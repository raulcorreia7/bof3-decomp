#include "game_00.h"

MATCH bool func_801BF11C(void) {
    PartyMember* work;
    s32          i;
    s32          j;
    s32          offset;
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

    g_EncounterOriginX = g_AreaScrollTargetX + (s_CameraScrollDeltas[g_Battle.scroll_dir].dx << 16);
    g_EncounterOriginY = g_AreaScrollTargetY + (s_CameraScrollDeltas[g_Battle.scroll_dir].dy << 16);

    for (i = 0; i < g_Game.party_size; i++) {
        work           = &g_Game.members[i];
        g_Game.current = work;
        TASK_SET(work);
        if (g_Task->param.unk_0B == 0) {
            if (func_801C29A0(8) & BYTE_MASK) {
                for (order = 0; order < PARTY_SLOT_COUNT; order++) {
                    if (g_PartyBattleOrder[order] == g_Game.current->chr.character_id) {
                        break;
                    }
                }
                g_Game.current->status.field.flags_12C.u8_value &= 0xFE;
                g_Task->draw_layer       = g_AreaDrawMode;
                g_Task->pos.x            = g_EncounterParty[order].x;
                g_Task->pos.y            = g_EncounterParty[order].y;
                COORD_INT(g_Task->pos.z) = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
                g_Task->unk_48           = 0;
                g_Task->param.unk_0B     = 1;
            }
        } else if (g_Task->param.unk_0B == 1) {
            if (func_801C2894(8) & BYTE_MASK) {
                /* CLEANUP: typed palette indexing reverses the source addition operands. */
                actor = g_Task;
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
                g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                g_Task->param.unk_0B = 0;
                ACTOR_CLEAR_TINT();
                g_Task->tint.bytes.flags = 0;
                g_Task->param.unk_0B     = 2;
            }
        }
        Actor_StepAnimLoop();
    }

    for (i = 0; i < g_Game.party_size; i++) {
        offset = i * BATTLE_PARTY_STRIDE;
        if ((&D_80145E9B)[offset] != 2) {
            return 0;
        }
    }

    return 1;
}
