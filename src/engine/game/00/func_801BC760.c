#include "game_00.h"

/* nonmatching unmeasured: tried the first draft cleaned; abs as if(v<0)v=-v, separate block temps; scheduler order of
 * the four D_80146144/48 product terms vs near-sum differs (51.9%). */
#ifdef NON_MATCHING
NON_MATCHING s32 func_801BC760(void) {
    PartyMember* row;
    s32          goal_x;
    s32          goal_y;
    s32          span;
    s32          da;
    s32          db;
    s32          dc;
    s32          dd;
    s32          dsum;
    s32          dx;
    s32          dy;
    s32          near_a;
    s32          near_b;
    s32          result;
    s32          tgt_x;
    s32          tgt_y;
    u8           dir;
    u8           count;
    u8           cnt2;
    PartyMember* saved;

    dir    = g_Task->direction_08;
    goal_x = g_Game.members[0].pos.x.fixed + (g_Game.members[0].unk_0C * g_Game.members[0].unk_09);
    goal_y = g_Game.members[0].pos.y.fixed + (g_Game.members[0].unk_10 * g_Game.members[0].unk_09);
    if (g_Game.members[g_Task->unk_05 ^ 3].u.field.mode_12B.u8_value != 9) {
        if (g_Task->unk_05 == 2) {
            if (D_80145FD6 == 0) {
                g_Task->unk_06 = 1;
            } else {
                g_Task->unk_06 = 0;
            }
        } else if ((u8)g_Game.party_size >= 3U) {
            da   = g_Task->pos.x.fixed - goal_x;
            da   = ABS(da);
            db   = g_Task->pos.y.fixed - goal_y;
            db   = ABS(db);
            dsum = da + db;
            dc   = (D_80146144 + (D_8014611C * D_80146119)) - goal_x;
            dc   = ABS(dc);
            dd   = (D_80146148 + (D_80146120 * D_80146119)) - goal_y;
            dd   = ABS(dd);
            if ((dc + dd) < dsum) {
                g_Task->unk_06 = 2;
            } else {
                g_Task->unk_06 = 0;
            }
        } else {
            g_Task->unk_06 = 0;
        }
    }
    row    = &g_Game.members[g_Task->unk_06];
    span   = TO_COORD(1) + COORD_HALF;
    tgt_x  = row->pos.x.fixed + (row->unk_0C * row->unk_09);
    near_a = tgt_x - (g_FacingSteps[row->facing].x * 2);
    tgt_y  = row->pos.y.fixed + (row->unk_10 * row->unk_09);
    near_b = tgt_y - (g_FacingSteps[row->facing].y * 2);
    if (row->unk_70 != 0) {
        span = TO_COORD(2);
    }
    dx = g_Task->pos.x.fixed - tgt_x;
    dx = ABS(dx);
    if (span >= dx) {
        dy = g_Task->pos.y.fixed - tgt_y;
        dy = ABS(dy);
        if (span >= dy) {
            return 1;
        }
    }
    func_801BCD60(near_a, near_b);
    dx = g_Task->pos.x.fixed - near_a;
    dx = ABS(dx);
    if (dx <= TO_COORD(6) && (dy = g_Task->pos.y.fixed - near_b, dy = dy < 0 ? -dy : dy) <= TO_COORD(6)) {
        if (dx > TO_COORD(2) || dy > TO_COORD(2)) {
            count = g_Game.members[g_Task->unk_06].u.field.counter_11C.u8_value + 1;
        } else {
            count = g_Game.members[g_Task->unk_06].u.field.counter_11C.u8_value;
        }
    } else {
        count = 5;
    }
    g_Game.current->u.field.counter_11C.s8_value = count;
    cnt2                                         = g_Game.current->u.field.counter_11C.s8_value;
    if (cnt2 >= 3U) {
        if (cnt2 >= 6U) {
            cnt2 = 5;
        }
    } else {
        cnt2 = 3;
    }
    g_Game.current->u.field.counter_11C.s8_value = cnt2;
    func_801BD290(near_a, near_b, (s8*)g_Task + 8);
    result = func_801BC4D0();
    if ((result & BYTE_MASK) != 1) {
        dx     = SP_REF(s32, 0x8) - near_a;
        dx     = ABS(dx);
        dy     = SP_REF(s32, 0xC) - near_b;
        dy     = ABS(dy);
        goal_x = g_Task->pos.x.fixed - near_a;
        goal_x = ABS(goal_x);
        goal_y = g_Task->pos.y.fixed - near_b;
        goal_y = ABS(goal_y);
        if ((goal_x + goal_y) < (dx + dy)) {
            g_Task->direction_08 = dir;
            result               = 1;
        }
        if ((result & BYTE_MASK) != 1) {
            return result & BYTE_MASK;
        }
    }
    if (!((g_Game.flags | g_Game.walk_flags) & BIT(0))) {
        if (*(u8*)g_Task & ACTOR_FLAG_OFFSCREEN) {
            saved          = g_Game.current;
            g_Game.current = g_Game.members;
            near_a = (g_Game.members[0].pos.x.fixed + (g_Game.members[0].unk_0C * g_Game.members[0].unk_09)) & ~0x7FFF;
            near_b = (g_Game.members[0].pos.y.fixed + (g_Game.members[0].unk_10 * g_Game.members[0].unk_09)) & ~0x7FFF;
            if (!(func_801C3E40(near_a, near_b, g_Task->state_70.byte, Area_ReadHeight(near_a, near_b)) & BYTE_MASK)) {
                g_Game.current = saved;
                *(u8*)g_Task |= ACTOR_FLAG_HIDDEN;
                g_Task->pos.x.fixed = near_a;
                g_Task->pos.y.fixed = near_b;
                g_Game.current->status.field.flags_12C.s8_value &= 0xFE;
                g_Game.current->status.field.flags_12C.s8_value |= (D_80145FBC & 1);
                COORD_INT(g_Task->pos.z) = Area_ReadHeight(near_a, near_b);
                g_Task->unk_29           = g_Game.members[0].unk_29;
                FIELD(s8, g_Task, 0x1u)  = 2;
                FIELD(s8, g_Task, 0x2u)  = 2;
                return 0xFF;
            }
            g_Game.current = saved;
        }
    }
    return result & BYTE_MASK;
}
#else
INCLUDE_ASM(func_801BC760);
#endif
