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

    if (g_Game.current->u.field.counter_11C.u8_value == 4) {
        work_a     = g_Task;
        work_count = work_a->option_flags;
        if (work_count < 17U) {
            work_a->option_flags = (work_count + 1);
        }
    } else {
        g_Task->option_flags = 0U;
    }
    level_flag = g_Game.current->u.field.counter_11C.u8_value;
    if (!(g_GameRequestFlags & 0x1)) {
        func_801C3828();
    }
    func_801C3598();
    func_801C2BEC();
    if (!(func_801C3790(0) & BYTE_MASK) && !(func_801C37DC(0) & BYTE_MASK) && !(func_801C2AAC() & BYTE_MASK)) {
        if (func_801C2B4C() & BYTE_MASK) {
            work_b = g_Task;
            Area_SetCellPalette(COORD_INT(work_b->pos.x), COORD_INT(work_b->pos.y));
            return;
        }
        state_flags = g_GameRequestFlags;
        if (state_flags & 0x1) {
            work_c = g_Task;
            if ((Area_GetCellCode(COORD_INT(work_c->pos.x), COORD_INT(work_c->pos.y)) & BYTE_MASK) == 0xAF) {
                func_801B5BDC(g_Task->direction_08);
                Game_RequestAreaChange(g_GameContextSeed, g_GameEntryPosX, g_GameEntryPosY, g_GameContextKind);
                g_GameEntryMode   = 0;
                g_GameRequestKind = 0xC;
                return;
            }
            if (g_Game.walk_flags & 0x2000) {
                g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
                func_801B5BDC(g_Task->direction_08);
                goto block_46; /* re-arm the frame flags */
            }
            work_d = g_Task;
            if ((Area_GetCellCode(COORD_INT(work_d->pos.x), COORD_INT(work_d->pos.y)) & BYTE_MASK) == 0xC0) {
                work_e = g_Task;
                func_801A0048(COORD_INT(work_e->pos.x), COORD_INT(work_e->pos.y));
            }
            goto block_24; /* continue with the front request */
        }
        if ((state_flags & 0x2) && ((work_f = g_Task, speed = work_f->state_70.byte, route_index2 = work_f->direction_08 * 2,
                                     pos_x = work_f->pos.x.fixed + ((*(s32*)((u8*)g_FacingSteps + route_index2 * 4)) * speed), pos_y = work_f->pos.y.fixed + (g_FacingStepY[route_index2] * speed),
                                     (pos_x == TO_COORD(2)) || (pos_y == TO_COORD(2)) || (pos_x == ((g_AreaMapBundle.width - 3) << 0x10)) || (pos_y == ((g_AreaMapBundle.height - 3) << 0x10))))) {
            Actor_RequestScript(g_Task->direction_08);
            Game_RequestAreaChange(D_80143F04, D_80143F08, D_80143F0C, FACING_DOWN_RIGHT);
            goto block_46; /* re-arm the frame flags */
        }
    block_24:
        work_g = g_Task;
        if (func_801C39D8(work_g->pos.x.fixed, work_g->pos.y.fixed, work_g->state_70.byte, 0xA7, 0U) & BYTE_MASK) {
            work_h = g_Task;
            func_801A0048(COORD_INT(work_h->pos.x), COORD_INT(work_h->pos.y));
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
            Actor_RequestScript(g_Task->direction_08);
            goto block_46; /* re-arm the frame flags */
        }
        work_i = g_Task;
        if (!(func_801C472C(work_i->pos.x.fixed, work_i->pos.y.fixed, work_i->state_70.byte, 0xA6, 0U) & BYTE_MASK)) {
            Actor_RequestScript(g_Task->direction_08);
            D_8014504A = 0;
            Game_RequestAreaChange(D_80145048, D_80145040, D_80145044, FACING_DOWN_RIGHT);
            return;
        }
        world_flags = g_AreaWalkFlags;
        if (world_flags & 0x20) {
            g_Game.walk_flags = world_flags ^ 0x20;
            func_801C24D0();
            work_j        = g_Task;
            work_j->timer = (work_j->timer - 1);
            func_801B0DFC();
            g_Task->header.step = 2;
            goto block_end; /* leave the frame flags alone */
        }
        counter          = g_EncounterSteps;
        g_EncounterSteps = counter + 1;
        route_id         = g_Task->direction_08;
        if ((route_id == 2) || (route_id == 6)) {
            g_EncounterSteps = counter + 2;
        }
        Actor_ClearVelocity();
        g_AreaCameraStep       = 0;
        g_AreaCameraHeightStep = 0;
        if (!(g_GameRequestFlags & 0x1) && !(g_Game.walk_flags & (0x20 | AREA_WALK_ENTRY_PENDING))) {
            if (Area_CanStartEncounter() & BYTE_MASK) {
                g_Game.current->u.field.counter_11C.u8_value = 3U;
                Actor_RequestScript(g_Task->direction_08);
                g_AreaWalkFlags |= AREA_WALK_TRANSITION;
                g_Task->header.mode = 5;
                ACTOR_CLEAR_STEP();
                return;
            }
            goto block_38; /* the request was not made */
        }
    block_38:
        g_Game.current->u.field.counter_11C.u8_value = 3U;
        if (!(Game_RequestRockKick(level_flag) & BYTE_MASK)) {
            work_k = g_Task;
            if (((s32 (*)(s32, s32))func_801A79A4)(work_k->pos.x.fixed, work_k->pos.y.fixed) != 0) {
                func_801B5BDC(g_Task->direction_08);
                goto block_46; /* re-arm the frame flags */
            }
            func_801C329C();
            if (!GAME_SCRIPT_ACTIVE() && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) && (g_Game.input & (g_InputMasks[FIELD_INPUT_INTERACT] | INPUT_DIRECTIONAL))) {
                func_801B0568();
                return;
            }
            func_801B5BDC(g_Task->direction_08);
            g_Game.current->u.field.mode_12B.u8_value = 0;
        block_46:
            g_Task->header.step = 1;
        block_end:;
        }
    }
}
