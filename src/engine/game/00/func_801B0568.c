#include "game_00.h"

MATCH void func_801B0568(void) {
    s32    tmp0;
    s32    val0;
    s32    tmp1;
    s32    tmp2;
    u8     tmp3;
    s32    tmp10;
    u8     tmp4;
    Actor* tmp5;
    Actor* tmp6;
    Actor* tmp7;
    Actor* tmp8;
    Actor* tmp9;

    if (!GAME_SCRIPT_ACTIVE() && !(g_AreaWalkFlags & AREA_WALK_ENTRY_PENDING) && !(func_801B6258() & BYTE_MASK) && !(Game_LeaderSwitchRequest() & BYTE_MASK) &&
        !(Game_MenuRequestField() & BYTE_MASK) && !(Game_RequestPersonalAction() & BYTE_MASK) && !(Game_CameraLookRequest() & BYTE_MASK) && !(Game_SceneCameraRequest() & BYTE_MASK)) {
        tmp9 = TASK(Actor);
        tmp4 = tmp9->unk_0A;
        if (tmp4 != 0) {
            tmp9->unk_0A = (tmp4 - 1);
            return;
        }
        if (!(Game_GetInput() & BYTE_MASK)) {
            Actor_RequestRoute(TASK(Actor)->direction);
            g_Game.current->u.field.counter.unsigned_value = 3U;
            g_Game.current->u.field.mode.value             = 0;
            Actor_ClearVelocity();
            TASK(Actor)->option_flags = 0;
            TASK(Actor)->timer        = 0U;
            TASK(Actor)->param.unk_0B = 0;
            g_AreaCameraSpeed         = 0;
            g_AreaCameraHeightDelta   = 0;
            TASK(Actor)->header.step  = 0;
            return;
        }
        tmp0 = func_801B0E44() & BYTE_MASK;
        if (tmp0 == 3) {
            goto case_3;
        }
        if (tmp0 < 4) {
            if (tmp0 == 1) {
                goto case_1;
            }
            if (tmp0 >= 2) {
                goto case_2;
            }
            if (tmp0 == 0) {
                goto case_0;
            }
            return;
        }
        if (tmp0 == 5) {
            goto case_5;
        }
        if (tmp0 < 5) {
            return;
        }
        if (tmp0 == 6) {
            goto case_6;
        }
        if (tmp0 == GAME_NONE) {
            goto case_255;
        }
        return;
        {
        case_0:
            if ((Area_GetActorFacingStepX() << 0x18) != 0) {
                g_Game.current->u.field.mode.value = 0;
                Actor_RequestRoute(TASK(Actor)->direction);
                goto block_35; /* shares the state-1 tail */
            }
            TASK(Actor)->param.unk_0B = 0;
            func_801B0C88();
            Area_RunWalk();
            func_801C4C48();
            TASK(Actor)->param.unk_0B = 0;
            if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
                if (g_Game.walk_flags & (AREA_WALK_TRANSITION | 0x2000)) {
                    tmp5         = TASK(Actor);
                    tmp1         = tmp5->timer;
                    tmp2         = tmp5->pos.x.fixed + (tmp5->vx * tmp1);
                    tmp10        = tmp5->pos.y.fixed + (tmp5->vy * tmp1);
                    tmp5->unk_06 = (tmp5->unk_06 - 1);
                    if ((TASK(Actor)->unk_06 == 0) || (Area_CellGetCode((tmp2 >> 0x10), (tmp10 >> 0x10)) & BYTE_MASK)) {
                        g_EncounterSteps = 0;
                        g_AreaWalkFlags &= ~(AREA_WALK_TRANSITION | 0x2000);
                        Area_EncounterRollThreshold(0U);
                    }
                } else if (Area_EncounterCanStart() & BYTE_MASK) {
                    func_801B6418();
                    g_GameEntryPosX     = TO_COORD(25);
                    g_GameEntryPosY     = TO_COORD(25);
                    g_GameEntryFacing   = 4;
                    TASK(Actor)->unk_06 = 4U;
                    g_Game.walk_flags |= AREA_WALK_TRANSITION;
                }
            }
            Actor_RequestRoute((TASK(Actor)->direction + 8) & BYTE_MASK);
            tmp6        = TASK(Actor);
            tmp6->timer = (tmp6->timer - 1);
            Actor_MovementUpdate();
            g_Game.current->u.field.mode.value = 1;
            TASK(Actor)->header.step           = 2;
            return;
        case_1:
            if (Game_RequestRockKick(g_Game.current->u.field.counter.unsigned_value) & BYTE_MASK) {
                return;
            }
            g_Game.current->u.field.mode.value             = 0;
            g_Game.current->u.field.counter.unsigned_value = 3U;
            TASK(Actor)->timer                             = 0U;
            Actor_RequestRoute(TASK(Actor)->direction);
            g_Game.current->u.field.mode.value = 0;
        block_35:
            TASK(Actor)->header.step = 1;
            Game_RequestGarrPush();
            return;
        case_2:
            g_Game.current->u.field.counter.unsigned_value = 3U;
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->header.mode = 2;
            TASK(Actor)->header.step = PARTY_MOVE_STEP_LADDER_TRANSIT;
            tmp7                     = TASK(Actor);
            tmp2                     = tmp7->direction;
            if ((tmp2 == FACING_UP) || (tmp2 == FACING_LEFT)) {
                tmp7->unk_03 = PARTY_LADDER_TRANSIT_UP;
            } else {
                tmp7->unk_03 = PARTY_LADDER_TRANSIT_DOWN;
            }
            g_Game.current->u.field.mode.value                = 3;
            g_Game.current->status.field.flags.unsigned_value = (g_Game.current->status.field.flags.unsigned_value | 0x2);
            g_AreaWalkFlags |= 0x80;
            return;
        case_3:
            val0                                           = 2;
            g_Game.current->u.field.counter.unsigned_value = 2U;
            Script_Request(TASK(Actor)->direction);
            TASK(Actor)->header.mode                          = 2;
            TASK(Actor)->header.step                          = PARTY_MOVE_STEP_WALK_TRANSIT;
            g_Game.current->u.field.mode.value                = 2;
            g_Game.current->status.field.flags.unsigned_value = (g_Game.current->status.field.flags.unsigned_value | 0x2);
            g_Game.walk_flags |= 0x100;
            return;
        case_5:
            val0                                           = 3;
            g_Game.current->u.field.counter.unsigned_value = 3U;
            Script_Request(TASK(Actor)->direction);
            g_Game.current->u.field.mode.value = 4;
            TASK(Actor)->header.mode           = 2;
            TASK(Actor)->header.step           = PARTY_MOVE_STEP_JUMP;
            return;
        case_6:
            val0                                           = 3;
            g_Game.current->u.field.counter.unsigned_value = 3U;
            Script_Request(TASK(Actor)->direction);
            g_Game.current->u.field.mode.value = 3;
            TASK(Actor)->header.mode           = FIELD_TASK_MODE_CLIMB;
            tmp8                               = TASK(Actor);
            tmp3                               = tmp8->direction;
            if ((tmp3 == FACING_UP) || (tmp3 == FACING_LEFT)) {
                tmp8->header.step = 0;
                return;
            }
            tmp8->header.step = 1;
            return;
        case_255:
            g_Game.current->u.field.mode.value             = 0;
            g_Game.current->u.field.counter.unsigned_value = 3U;
            TASK(Actor)->timer                             = 0U;
            TASK(Actor)->param.unk_0B                      = 0;
            Actor_RequestRoute(TASK(Actor)->direction);
            g_Game.current->u.field.mode.value = 0;
            return;
        }
    }
}
