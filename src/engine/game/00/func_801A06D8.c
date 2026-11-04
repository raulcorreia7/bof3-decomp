#include "game_00.h"

MATCH u32 func_801A06D8(void) {
    Actor* row;
    u32    result;
    u8     i;
    u8     n;
    u8     j;
    u8     flags;

    result = g_AreaWalkFlags & AREA_WALK_STEP_ACTIVE;
    if (result == 0) {
        for (i = 0; i < ENTITY_MAX; i++) {
            row            = &g_Actors[i];
            g_SpadWork     = row;
            g_CurrentActor = row;
            if (!ACTOR_IN_USE(*row)) {
                continue;
            }
            SP_REF(s8, 0x3) = 0;
            if (row->unk_09 == 0 && (g_Actors[i].flags_74 & ACTOR_FLAG_SCRIPT_PENDING)) {
                if (g_Actors[i].flags_74 & ACTOR_FLAG_SCRIPT_REQUEST) {
                    if ((s8)func_801A17A0(&g_Actors[i].flags_74) &&
                        !(g_SpadWork->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                        g_Actors[i].unk_79 = g_SpadWork->direction_08 & 7;
                        if (!(g_SpadWork->option_flags & ACTOR_OPT_KEEP_FACING)) {
                            g_SpadWork->direction_08 = (D_80145E98 ^ 4) & 7;
                            func_8015BAC4(g_SpadWork->direction_08);
                        } else {
                            func_8015BAC4(g_SpadWork->direction_08 & 7);
                        }
                        if (g_SpadWork->unk_01 == 0xA) {
                            g_Actors[i].unk_79 |= 1;
                        }
                    }
                } else {
                    func_801A18C8(row);
                }
            } else if (g_CurrentActor->flags_74 & ACTOR_FLAG_INTERACTION_PENDING) {
                func_801A3A08();
                continue;
            } else if (g_Actors[i].roll_90 >= 0x1F && g_SpadWork->unk_09 == 0) {
                func_801A27C4(&g_Actors[i]);
            } else {
                D_801C83D8[g_SpadWork->unk_01](&g_Actors[i]);
            }
            if (g_SpadWork->unk_06 == 0xA) {
                continue;
            }
            flags = g_Actors[i].flags_74;
            if (!(flags & 0x40)) {
                if (flags & ACTOR_FLAG_MOVING) {
                    func_8015BAC4(g_SpadWork->direction_08);
                    g_Actors[i].flags_74 &= ~ACTOR_FLAG_MOVING;
                } else if (!(g_SpadWork->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                    n = g_Actors[i].unk_78 - 2 < 0 ? 0 : g_Actors[i].unk_78 - 2;
                    j = 0;
                    do {
                        j++;
                        func_8014D978();
                    } while (j <= n);
                }
            } else if (!(g_SpadWork->option_flags & ACTOR_OPT_WAIT_STREAM)) {
                if (g_SpadWork->flags_00 & ACTOR_FLAG_STEP_MOVE) {
                    func_8014D978();
                } else {
                    func_8014DAEC();
                }
            }
        }
        result     = (u16)D_80143F22;
        D_80146878 = result;
    }
    return result;
}
