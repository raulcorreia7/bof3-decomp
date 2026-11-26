#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801BC760(void) {
    PartyMember* member;
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

    dir    = SELF(Actor)->direction;
    goal_x = g_Game.members[0].pos.x.fixed + (g_Game.members[0].unk_0C * g_Game.members[0].unk_09);
    goal_y = g_Game.members[0].pos.y.fixed + (g_Game.members[0].unk_10 * g_Game.members[0].unk_09);
    if (g_Game.members[SELF(Actor)->unk_05 ^ 3].u.field.mode.unsigned_value != 9) {
        if (SELF(Actor)->unk_05 == 2) {
            if (g_Game.members[1].pad_06 == 0) {
                SELF(Actor)->unk_06 = 1;
            } else {
                SELF(Actor)->unk_06 = 0;
            }
        } else if ((u8)g_PartySize >= 3U) {
            da   = SELF(Actor)->pos.x.fixed - goal_x;
            da   = ABS(da);
            db   = SELF(Actor)->pos.y.fixed - goal_y;
            db   = ABS(db);
            dsum = da + db;
            dc   = (g_Game.members[2].pos.x.fixed + (g_Game.members[2].unk_0C * g_Game.members[2].unk_09)) - goal_x;
            dc   = ABS(dc);
            dd   = (g_Game.members[2].pos.y.fixed + (g_Game.members[2].unk_10 * g_Game.members[2].unk_09)) - goal_y;
            dd   = ABS(dd);
            if ((dc + dd) < dsum) {
                SELF(Actor)->unk_06 = 2;
            } else {
                SELF(Actor)->unk_06 = 0;
            }
        } else {
            SELF(Actor)->unk_06 = 0;
        }
    }
    member = &g_Game.members[SELF(Actor)->unk_06];
    span   = TO_COORD(1) + COORD_HALF;
    tgt_x  = member->pos.x.fixed + (member->unk_0C * member->unk_09);
    near_a = tgt_x - (g_FacingSteps[member->facing].x * 2);
    tgt_y  = member->pos.y.fixed + (member->unk_10 * member->unk_09);
    near_b = tgt_y - (g_FacingSteps[member->facing].y * 2);
    if (member->speed != 0) {
        span = TO_COORD(2);
    }
    dx = SELF(Actor)->pos.x.fixed - tgt_x;
    dx = ABS(dx);
    if (span >= dx) {
        dy = SELF(Actor)->pos.y.fixed - tgt_y;
        dy = ABS(dy);
        if (span >= dy) {
            return 1;
        }
    }
    func_801BCD60(near_a, near_b);
    dx = SELF(Actor)->pos.x.fixed - near_a;
    dx = ABS(dx);
    if (dx <= TO_COORD(6) && (dy = SELF(Actor)->pos.y.fixed - near_b, dy = dy < 0 ? -dy : dy) <= TO_COORD(6)) {
        if (dx > TO_COORD(2) || dy > TO_COORD(2)) {
            count = g_Game.members[SELF(Actor)->unk_06].u.field.counter.unsigned_value + 1;
        } else {
            count = g_Game.members[SELF(Actor)->unk_06].u.field.counter.unsigned_value;
        }
    } else {
        count = 5;
    }
    g_GameState->u.field.counter.value = count;
    cnt2                               = g_GameState->u.field.counter.value;
    if (cnt2 >= 3U) {
        if (cnt2 >= 6U) {
            cnt2 = 5;
        }
    } else {
        cnt2 = 3;
    }
    g_GameState->u.field.counter.value = cnt2;
    func_801BD290(near_a, near_b, SELF(s8) + 8);
    result = func_801BC4D0();
    if ((result & BYTE_MASK) != 1) {
        dx     = SP_REF(s32, 0x8) - near_a;
        dx     = ABS(dx);
        dy     = SP_REF(s32, 0xC) - near_b;
        dy     = ABS(dy);
        goal_x = SELF(Actor)->pos.x.fixed - near_a;
        goal_x = ABS(goal_x);
        goal_y = SELF(Actor)->pos.y.fixed - near_b;
        goal_y = ABS(goal_y);
        if ((goal_x + goal_y) < (dx + dy)) {
            SELF(Actor)->direction = dir;
            result                 = 1;
        }
        if ((result & BYTE_MASK) != 1) {
            return result & BYTE_MASK;
        }
    }
    if (!((g_GameFlags | g_AreaWalkFlags) & BIT(0))) {
        if (*SELF(u8) & ACTOR_FLAG_OFFSCREEN) {
            saved       = g_GameState;
            g_GameState = g_Game.members;
            near_a      = (g_Game.members[0].pos.x.fixed + (g_Game.members[0].unk_0C * g_Game.members[0].unk_09)) & ~0x7FFF;
            near_b      = (g_Game.members[0].pos.y.fixed + (g_Game.members[0].unk_10 * g_Game.members[0].unk_09)) & ~0x7FFF;
            if (!(Game_TestPlacement(near_a, near_b, SELF(Actor)->voice_flags.scene_flag, Area_HeightRead(near_a, near_b)) & BYTE_MASK)) {
                g_GameState = saved;
                *SELF(u8) |= ACTOR_FLAG_HIDDEN;
                SELF(Actor)->pos.x.fixed = near_a;
                SELF(Actor)->pos.y.fixed = near_b;
                g_GameState->status.field.flags.value &= 0xFE;
                g_GameState->status.field.flags.value |= (g_Game.members[0].status.field.flags.value & 1);
                COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(near_a, near_b);
                SELF(Actor)->draw_layer       = g_Game.members[0].unk_29;
                FIELD(s8, g_Self, 0x1u)       = 2;
                FIELD(s8, g_Self, 0x2u)       = 2;
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
