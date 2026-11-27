#include "game_00.h"
#include "menu/save_data.h"

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

    if (g_Game.current->u.field.counter.unsigned_value == 4) {
        work_a     = SELF(Actor);
        work_count = work_a->option_flags;
        if (work_count < 17U) {
            work_a->option_flags = (work_count + 1);
        }
    } else {
        SELF(Actor)->option_flags = 0U;
    }
    level_flag = g_Game.current->u.field.counter.unsigned_value;
    if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)) {
        func_801C3828();
    }
    Party_TickConfusion();
    Party_FloorDamageUpdate();
    if (!(func_801C3790(0) & BYTE_MASK) && !(func_801C37DC(0) & BYTE_MASK) && !(Party_StartCellWalk() & BYTE_MASK)) {
        if (Party_StartFallThrough() & BYTE_MASK) {
            work_b = SELF(Actor);
            Area_CellSetPalette(COORD_INT(work_b->pos.x), COORD_INT(work_b->pos.y));
            return;
        }
        state_flags = g_GameRequestFlags;
        if (state_flags & AREA_LOAD_FLAG_WORLD_MAP) {
            work_c = SELF(Actor);
            if ((Area_CellGetCode(COORD_INT(work_c->pos.x), COORD_INT(work_c->pos.y)) & BYTE_MASK) == 0xAF) {
                Actor_RequestRoute(SELF(Actor)->direction);
                Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);
                g_GameEntryMode   = 0;
                g_GameRequestType = 0xC;
                return;
            }
            if (g_Game.walk_flags & 0x2000) {
                g_Game.flags |= GAME_FLAG_SCRIPT_ACTIVE;
                Actor_RequestRoute(SELF(Actor)->direction);
                goto block_46; /* re-arm the frame flags */
            }
            work_d = SELF(Actor);
            if ((Area_CellGetCode(COORD_INT(work_d->pos.x), COORD_INT(work_d->pos.y)) & BYTE_MASK) == 0xC0) {
                work_e = SELF(Actor);
                Area_RequestLinkAtCell(COORD_INT(work_e->pos.x), COORD_INT(work_e->pos.y));
            }
            goto block_24; /* continue with the front request */
        }
        if ((state_flags & 0x2) && ((work_f = SELF(Actor), speed = work_f->voice_flags.scene_flag, route_index2 = work_f->direction * 2,
                                     pos_x = work_f->pos.x.fixed + ((*(s32*)((u8*)g_FacingSteps + route_index2 * 4)) * speed), pos_y = work_f->pos.y.fixed + (g_FacingStepY[route_index2] * speed),
                                     (pos_x == TO_COORD(2)) || (pos_y == TO_COORD(2)) || (pos_x == ((g_AreaMapBundle.width - 3) << 0x10)) || (pos_y == ((g_AreaMapBundle.height - 3) << 0x10))))) {
            Script_Request(SELF(Actor)->direction);
            Game_RequestAreaChange(g_GameLastAreaId, g_GameLastX, g_GameLastY, FACING_DOWN_RIGHT);
            goto block_46; /* re-arm the frame flags */
        }
    block_24:
        work_g = SELF(Actor);
        if (Game_TestMapCells(work_g->pos.x.fixed, work_g->pos.y.fixed, work_g->voice_flags.scene_flag, 0xA7, 0U) & BYTE_MASK) {
            work_h = SELF(Actor);
            Area_RequestLinkAtCell(COORD_INT(work_h->pos.x), COORD_INT(work_h->pos.y));
            g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
            Script_Request(SELF(Actor)->direction);
            goto block_46; /* re-arm the frame flags */
        }
        work_i = SELF(Actor);
        if (!(Area_CellTestCorners(work_i->pos.x.fixed, work_i->pos.y.fixed, work_i->voice_flags.scene_flag, 0xA6, 0U) & BYTE_MASK)) {
            Script_Request(SELF(Actor)->direction);
            g_SaveData.return_point.pending = 0;
            Game_RequestAreaChange(g_SaveData.return_point.area_id, g_SaveData.return_point.x, g_SaveData.return_point.y, FACING_DOWN_RIGHT);
            return;
        }
        world_flags = g_AreaWalkFlags;
        if (world_flags & 0x20) {
            g_Game.walk_flags = world_flags ^ 0x20;
            Area_RunWalk();
            work_j        = SELF(Actor);
            work_j->timer = (work_j->timer - 1);
            Actor_MovementUpdate();
            SELF(Actor)->header.step = 2;
            goto block_end; /* leave the frame flags alone */
        }
        counter          = g_EncounterSteps;
        g_EncounterSteps = counter + 1;
        route_id         = SELF(Actor)->direction;
        if ((route_id == FACING_UP_RIGHT) || (route_id == FACING_DOWN_LEFT)) {
            g_EncounterSteps = counter + 2;
        }
        Actor_ClearVelocity();
        g_AreaCameraSpeed       = 0;
        g_AreaCameraHeightDelta = 0;
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) && !(g_Game.walk_flags & (0x20 | AREA_WALK_ENTRY_PENDING))) {
            if (Area_EncounterCanStart() & BYTE_MASK) {
                g_Game.current->u.field.counter.unsigned_value = 3U;
                Script_Request(SELF(Actor)->direction);
                g_AreaWalkFlags |= AREA_WALK_TRANSITION;
                SELF(Actor)->header.mode = 5;
                ACTOR_CLEAR_STEP();
                return;
            }
            goto block_38; /* the request was not made */
        }
    block_38:
        g_Game.current->u.field.counter.unsigned_value = 3U;
        if (!(Game_RequestRockKick(level_flag) & BYTE_MASK)) {
            work_k = SELF(Actor);
            if (((s32 (*)(s32, s32))func_801A79A4)(work_k->pos.x.fixed, work_k->pos.y.fixed) != 0) {
                Actor_RequestRoute(SELF(Actor)->direction);
                goto block_46; /* re-arm the frame flags */
            }
            func_801C329C();
            if (!GAME_SCRIPT_ACTIVE() && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) && (g_Game.input & (g_InputMasks[FIELD_INPUT_INTERACT] | INPUT_DIRECTIONAL))) {
                func_801B0568();
                return;
            }
            Actor_RequestRoute(SELF(Actor)->direction);
            g_Game.current->u.field.mode.unsigned_value = 0;
        block_46:
            SELF(Actor)->header.step = 1;
        block_end:;
        }
    }
}
