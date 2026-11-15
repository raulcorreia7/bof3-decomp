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

    tmp5 = g_Task;
    if (g_GameStateIndex == GAME_REQUEST_SCENE_CAMERA) {
        tmp5->header.mode = 0xE;
        goto block_26; /* retail branch */
    }
    if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        tmp5->header.mode   = 5;
        g_Task->header.step = 0;
        tmp9                = g_Task;
        tmp9->param.unk_0B  = 0;
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
                    Actor_RequestScript(g_Task->direction_08);
                    g_Task->header.mode = 7;
                    goto block_26; /* retail branch */
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
                        Actor_RequestScript(g_Task->direction_08);
                        goto block_26; /* retail branch */
                    }
                    if (!(g_Characters[g_Game.current->character_index].status & STATUS_CONFUSED)) {
                        g_Game.current->u.field.step_12A.s8_value = 0;
                    }
                    func_801C2538();
                    func_801C4C48();
                    Actor_RequestScript((g_Task->direction_08 + 8) & BYTE_MASK);
                    if (g_Game.current->chr.character_id == CHAR_ID_GARR) {
                        tmp10 = g_Task;
                        tmp3  = tmp10->timer;
                        Area_ReadHeight(tmp10->pos.x.fixed + (tmp10->vx * tmp3), tmp10->pos.y.fixed + (tmp10->vy * tmp3));
                    }
                    tmp11        = g_Task;
                    tmp11->timer = (tmp11->timer - 1);
                    Actor_UpdateMovement();
                    g_Game.current->u.field.mode_12B.s8_value = 1;
                    tmp6                                      = g_Task;
                    tmp6->header.step                         = 1;
                    return;
                case_b:
                    Actor_ClearVelocity();
                    Actor_RequestScript(g_Task->direction_08);
                    g_Game.current->u.field.mode_12B.s8_value = 0;
                block_26:
                    tmp7              = g_Task;
                    tmp7->header.step = 0;
                    return;
                case_5:
                    g_Game.current->u.field.counter_11C.s8_value = 3;
                    Actor_RequestScript(g_Task->direction_08);
                    g_Game.current->u.field.mode_12B.s8_value = 4;
                    g_Task->header.mode                       = 2;
                    tmp8                                      = g_Task;
                    tmp8->header.step                         = 3;
                    return;
                case_6:
                    g_Game.current->u.field.counter_11C.s8_value = 3;
                    Actor_RequestScript(g_Task->direction_08);
                    g_Game.current->u.field.mode_12B.s8_value = 3;
                    g_Task->header.mode                       = FIELD_TASK_MODE_CLIMB;
                    tmp12                                     = g_Task;
                    tmp4                                      = tmp12->direction_08;
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
