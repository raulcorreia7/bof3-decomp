#include "game_00.h"

MATCH void func_801B146C(void) {
    u8     state_flags;
    u8     level_flag;
    u8     work_count;
    u8     speed;
    u8     route_id;
    u16    counter;
    u16    world_flags;
    s32    pos_x;
    s32    pos_y;
    s32    route_index2;
    Actor* work_a;
    Actor* work_b;
    Actor* work_c;
    Actor* work_d;
    Actor* work_e;
    Actor* work_f;
    Actor* work_g;
    Actor* work_h;
    Actor* work_i;
    Actor* work_j;
    Actor* work_k;

    if (g_GameState->counter_11C.u8_value == 4) {
        work_a     = g_SpadWork;
        work_count = work_a->option_flags;
        if (work_count < 0x11U) {
            work_a->option_flags = (u8)(work_count + 1);
        }
    } else {
        g_SpadWork->option_flags = 0U;
    }
    level_flag = g_GameState->counter_11C.u8_value;
    if (!(g_GameRequestFlags & 1)) {
        func_801C3828();
    }
    func_801C3598();
    func_801C2BEC();
    if (!(func_801C3790(0) & BYTE_MASK) && !(func_801C37DC(0) & BYTE_MASK) && !(func_801C2AAC() & BYTE_MASK)) {
        if (func_801C2B4C() & BYTE_MASK) {
            work_b = g_SpadWork;
            Area_SetCellPalette(work_b->x.part.integer, work_b->y.part.integer);
            return;
        }
        state_flags = g_GameRequestFlags;
        if (state_flags & 1) {
            work_c = g_SpadWork;
            if ((Area_GetCellCode(work_c->x.part.integer, work_c->y.part.integer) & BYTE_MASK) == 0xAF) {
                func_801B5BDC(g_SpadWork->direction_08);
                Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
                g_GameEntryMode   = 0;
                g_GameRequestKind = 0xC;
                return;
            }
            if (g_AreaWalkFlags & 0x2000) {
                g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
                func_801B5BDC(g_SpadWork->direction_08);
                goto block_46; /* re-arm the frame flags */
            }
            work_d = g_SpadWork;
            if ((Area_GetCellCode(work_d->x.part.integer, work_d->y.part.integer) & BYTE_MASK) == 0xC0) {
                work_e = g_SpadWork;
                func_801A0048(work_e->x.part.integer, work_e->y.part.integer);
            }
            goto block_24; /* continue with the front request */
        }
        if ((state_flags & 2) &&
            ((work_f = g_SpadWork, speed = work_f->state_70.byte, route_index2 = work_f->direction_08 * 2,
              pos_x = work_f->x.fixed + ((*(s32*)((u8*)g_FacingSteps + route_index2 * 4)) * speed),
              pos_y = work_f->y.fixed + (D_80181B98[route_index2] * speed),
              (pos_x == 0x20000) || (pos_y == 0x20000) || (pos_x == ((D_80104000 - 3) << 0x10)) ||
                  (pos_y == ((D_80104001 - 3) << 0x10))))) {
            Actor_RequestScript(g_SpadWork->direction_08);
            Game_RequestAreaChange(LOHU(D_80143F04), LOWU(D_80143F08), LOWU(D_80143F0C), 4U);
            goto block_46; /* re-arm the frame flags */
        }
    block_24:
        work_g = g_SpadWork;
        if (func_801C39D8(work_g->x.fixed, work_g->y.fixed, work_g->state_70.byte, 0xA7, 0U) & BYTE_MASK) {
            work_h = g_SpadWork;
            func_801A0048(work_h->x.part.integer, work_h->y.part.integer);
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
            Actor_RequestScript(g_SpadWork->direction_08);
            goto block_46; /* re-arm the frame flags */
        }
        work_i = g_SpadWork;
        if (!(func_801C472C(work_i->x.fixed, work_i->y.fixed, work_i->state_70.byte, 0xA6, 0U) & BYTE_MASK)) {
            Actor_RequestScript(g_SpadWork->direction_08);
            D_8014504A = 0;
            Game_RequestAreaChange(D_80145048, (u32)D_80145040, (u32)D_80145044, 4U);
            return;
        }
        world_flags = g_AreaWalkFlags;
        if (world_flags & 0x20) {
            g_AreaWalkFlags = world_flags ^ 0x20;
            func_801C24D0();
            work_j         = g_SpadWork;
            work_j->unk_09 = (u8)(work_j->unk_09 - 1);
            func_801B0DFC();
            g_SpadWork->state_02 = 2;
            goto block_end; /* leave the frame flags alone */
        }
        counter    = (u16)D_80143F22;
        D_80143F22 = counter + 1;
        route_id   = g_SpadWork->direction_08;
        if ((route_id == 2) || (route_id == 6)) {
            D_80143F22 = counter + 2;
        }
        Actor_ClearVelocity();
        g_AreaCameraStep       = 0;
        g_AreaCameraHeightStep = 0;
        if (!(g_GameRequestFlags & 1) && !(g_AreaWalkFlags & (0x20 | AREA_WALK_ENTRY_PENDING))) {
            if (Area_CanStartEncounter() & BYTE_MASK) {
                g_GameState->counter_11C.u8_value = 3U;
                Actor_RequestScript(g_SpadWork->direction_08);
                g_AreaWalkFlags |= AREA_WALK_TRANSITION;
                g_SpadWork->unk_01 = 5;
                ACTOR_CLEAR_STATE();
                return;
            }
            goto block_38; /* the request was not made */
        }
    block_38:
        g_GameState->counter_11C.u8_value = 3U;
        if (!(func_801B5F68(level_flag) & BYTE_MASK)) {
            work_k = g_SpadWork;
            if (((s32 (*)(s32, s32))func_801A79A4)(work_k->x.fixed, work_k->y.fixed) != 0) {
                func_801B5BDC(g_SpadWork->direction_08);
                goto block_46; /* re-arm the frame flags */
            }
            func_801C329C();
            if (!GAME_SCRIPT_ACTIVE() && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) &&
                (D_8014625C & (g_InputMasks | INPUT_DIRECTIONAL))) {
                func_801B0568();
                return;
            }
            func_801B5BDC(g_SpadWork->direction_08);
            g_GameState->mode_12B.u8_value = 0;
        block_46:
            g_SpadWork->state_02 = 1;
        block_end:;
        }
    }
}
