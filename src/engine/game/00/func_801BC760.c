#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned; abs as if(v<0)v=-v, separate block temps; scheduler order of the four
 * D_80146144/48 product terms vs near-sum differs (51.9%). */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801BC760(void) {
    PartyBattler*    row;
    s32              goal_x;
    s32              goal_y;
    s32              span;
    s32              da;
    s32              db;
    s32              dc;
    s32              dd;
    s32              dsum;
    s32              dx;
    s32              dy;
    s32              near_a;
    s32              near_b;
    s32              result;
    s32              tgt_x;
    s32              tgt_y;
    u8               dir;
    u8               count;
    u8               cnt2;
    GameStateRecord* saved;

    dir    = g_SpadWork->route_index_08;
    goal_x = D_80145EC4 + (D_80145E9C * D_80145E99);
    goal_y = D_80145EC8 + (D_80145EA0 * D_80145E99);
    if (D_80145FBB[g_SpadWork->unk_05 ^ 3].mode != 9) {
        if (g_SpadWork->unk_05 == 2) {
            if (D_80145FD6 == 0) {
                g_SpadWork->unk_06 = 1;
            } else {
                g_SpadWork->unk_06 = 0;
            }
        } else if ((u8)g_PartySize >= 3U) {
            da = g_SpadWork->x.fixed - goal_x;
            if (da < 0) {
                da = -da;
            }
            db = g_SpadWork->y.fixed - goal_y;
            if (db < 0) {
                db = -db;
            }
            dsum = da + db;
            dc   = (D_80146144 + (D_8014611C * D_80146119)) - goal_x;
            if (dc < 0) {
                dc = -dc;
            }
            dd = (D_80146148 + (D_80146120 * D_80146119)) - goal_y;
            if (dd < 0) {
                dd = -dd;
            }
            if ((dc + dd) < dsum) {
                g_SpadWork->unk_06 = 2;
            } else {
                g_SpadWork->unk_06 = 0;
            }
        } else {
            g_SpadWork->unk_06 = 0;
        }
    }
    row    = &g_BattlePartyBattlers[g_SpadWork->unk_06];
    span   = 0x18000;
    tgt_x  = row->coord_x_34.raw + (row->unk_0C * row->unk_09);
    near_a = tgt_x - (g_FacingSteps[row->unk_08].x * 2);
    tgt_y  = row->coord_y_38.raw + (row->unk_10 * row->unk_09);
    near_b = tgt_y - (g_FacingSteps[row->unk_08].y * 2);
    if (row->unk_70 != 0) {
        span = 0x20000;
    }
    dx = g_SpadWork->x.fixed - tgt_x;
    if (dx < 0) {
        dx = -dx;
    }
    if (span >= dx) {
        dy = g_SpadWork->y.fixed - tgt_y;
        if (dy < 0) {
            dy = -dy;
        }
        if (span >= dy) {
            return 1;
        }
    }
    func_801BCD60(near_a, near_b);
    dx = g_SpadWork->x.fixed - near_a;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx <= 0x60000 && (dy = g_SpadWork->y.fixed - near_b, dy = dy < 0 ? -dy : dy) <= 0x60000) {
        if (dx > 0x20000 || dy > 0x20000) {
            count = *(&D_80145FAC + (g_SpadWork->unk_06 * BATTLE_PARTY_STRIDE)) + 1;
        } else {
            count = *(&D_80145FAC + (g_SpadWork->unk_06 * BATTLE_PARTY_STRIDE));
        }
    } else {
        count = 5;
    }
    g_GameState->counter_11C.s8_value = count;
    cnt2                              = g_GameState->counter_11C.s8_value;
    if (cnt2 >= 3U) {
        if (cnt2 >= 6U) {
            cnt2 = 5;
        }
    } else {
        cnt2 = 3;
    }
    g_GameState->counter_11C.s8_value = cnt2;
    func_801BD290(near_a, near_b, (s8*)g_SpadWork + 8);
    result = func_801BC4D0();
    if ((result & BYTE_MASK) != 1) {
        dx = SP_REF(s32, 0x8) - near_a;
        if (dx < 0) {
            dx = -dx;
        }
        dy = SP_REF(s32, 0xC) - near_b;
        if (dy < 0) {
            dy = -dy;
        }
        goal_x = g_SpadWork->x.fixed - near_a;
        if (goal_x < 0) {
            goal_x = -goal_x;
        }
        goal_y = g_SpadWork->y.fixed - near_b;
        if (goal_y < 0) {
            goal_y = -goal_y;
        }
        if ((goal_x + goal_y) < (dx + dy)) {
            g_SpadWork->route_index_08 = dir;
            result                     = 1;
        }
        if ((result & BYTE_MASK) != 1) {
            return result & BYTE_MASK;
        }
    }
    if (!((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_BUSY(0))) {
        if (*(u8*)g_SpadWork & ACTOR_FLAG_OFFSCREEN) {
            saved       = g_GameState;
            g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
            near_a      = (D_80145EC4 + (D_80145E9C * D_80145E99)) & ~0x7FFF;
            near_b      = (D_80145EC8 + (D_80145EA0 * D_80145E99)) & ~0x7FFF;
            if (!(func_801C3E40(near_a, near_b, g_SpadWork->state_70.byte, Area_ReadHeight(near_a, near_b)) &
                  BYTE_MASK)) {
                g_GameState = saved;
                *(u8*)g_SpadWork |= ACTOR_FLAG_HIDDEN;
                g_SpadWork->x.fixed = near_a;
                g_SpadWork->y.fixed = near_b;
                g_GameState->flags_12C.s8_value &= 0xFE;
                g_GameState->flags_12C.s8_value |= (D_80145FBC & 1);
                g_SpadWork->z.part.integer  = Area_ReadHeight(near_a, near_b);
                g_SpadWork->unk_29          = D_80145EB9;
                FIELD(s8, g_SpadWork, 0x1u) = 2;
                FIELD(s8, g_SpadWork, 0x2u) = 2;
                return 0xFF;
            }
            g_GameState = saved;
        }
    }
    return result & BYTE_MASK;
}
#else
INCLUDE_ASM(func_801BC760);
#endif
