#include "game_00.h"

MATCH void func_801BC000(void) {
    s32    tmp0;
    s32    not_zero;
    s32    bit;
    s32    tmp1;
    s32    tmp2;
    s32    val0;
    u8     ret;
    u8     tmp3;
    u8     tmp4;
    Actor* tmp5;
    Actor* tmp6;
    Actor* tmp7;
    Actor* tmp8;
    Actor* tmp9;
    Actor* tmp10;
    Actor* tmp11;
    Actor* tmp12;

    tmp5 = TASK(Actor);
    if (g_GameStateIndex == GAME_REQUEST_SCENE_CAMERA) {
        tmp5->header.mode = 0xE;
        goto block_26;
    }
    if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        tmp5->header.mode        = 5;
        TASK(Actor)->header.step = 0;
        tmp9                     = TASK(Actor);
        tmp9->param.unk_0B       = 0;
        return;
    }
    bit = g_Game.walk_flags & AREA_WALK_LEADER_SWITCH_ACTIVE;
    if (!bit && !(g_Game.walk_flags & AREA_WALK_MENU_ACTIVE)) {
        ret = func_801C3790(1) & BYTE_MASK;
        if (ret != 0) {
            return;
        }
        ret = func_801C37DC(1) & BYTE_MASK;
        if (ret != 0) {
            return;
        }
        {
            {
                if (*D_80145E91 == 0xA) {
                    Script_Request(TASK(Actor)->direction);
                    TASK(Actor)->header.mode = 7;
                    goto block_26;
                }
                if ((func_801BD938() & BYTE_MASK) == 0) {
                    tmp2 = func_801BC760() & BYTE_MASK;
                    if (tmp2 < 5) {
                        not_zero = tmp2 != 0;
                        if (not_zero) {
                            goto case_b;
                        }
                        if (tmp2 == 0) {
                            goto case_a;
                        }
                        return;
                    }
                    if (tmp2 == 6) {
                        goto case_6;
                    }
                    if (tmp2 < 6) {
                        goto case_5;
                    }
                    return;
                case_a:
                    if ((Area_GetActorFacingStepX() << 0x18) != 0) {
                        Script_Request(TASK(Actor)->direction);
                        goto block_26;
                    }
                    if (!(g_Characters[g_Game.current->character_index].status & STATUS_CONFUSED)) {
                        g_Game.current->u.field.step.value = 0;
                    }
                    Area_SetWalkVelocity();
                    func_801C4C48();
                    Script_Request((TASK(Actor)->direction + 8) & BYTE_MASK);
                    if (g_Game.current->chr.character_id == CHAR_ID_GARR) {
                        tmp10 = TASK(Actor);
                        tmp3  = tmp10->timer;
                        Area_HeightRead(tmp10->pos.x.fixed + (tmp10->vx * tmp3), tmp10->pos.y.fixed + (tmp10->vy * tmp3));
                    }
                    tmp11        = TASK(Actor);
                    tmp11->timer = (tmp11->timer - 1);
                    Actor_MovementUpdate();
                    g_Game.current->u.field.mode.value = 1;
                    tmp6                               = TASK(Actor);
                    tmp6->header.step                  = 1;
                    return;
                case_b:
                    Actor_ClearVelocity();
                    Script_Request(TASK(Actor)->direction);
                    g_Game.current->u.field.mode.value = 0;
                block_26:
                    tmp7              = TASK(Actor);
                    tmp7->header.step = 0;
                    return;
                case_5:
                    g_Game.current->u.field.counter.value = 3;
                    Script_Request(TASK(Actor)->direction);
                    g_Game.current->u.field.mode.value = 4;
                    TASK(Actor)->header.mode           = 2;
                    tmp8                               = TASK(Actor);
                    tmp8->header.step                  = PARTY_MOVE_STEP_JUMP;
                    return;
                case_6:
                    g_Game.current->u.field.counter.value = 3;
                    Script_Request(TASK(Actor)->direction);
                    g_Game.current->u.field.mode.value = 3;
                    TASK(Actor)->header.mode           = FIELD_TASK_MODE_CLIMB;
                    tmp12                              = TASK(Actor);
                    tmp4                               = tmp12->direction;
                    if ((tmp4 == FACING_UP) || (tmp4 == FACING_LEFT)) {
                        tmp12->header.step = 0;
                        return;
                    }
                    tmp12->header.step = 1;
                    return;
                }
                return;
            }
        }
    }
    return;
}
