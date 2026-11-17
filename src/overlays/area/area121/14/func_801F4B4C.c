#include "area121_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4B4C(s32 input) {
    s32    step_result;
    s32    facing_delta;
    s32    adjusted_facing_delta;
    u8     saved_facing;
    u8     current_facing;
    u8     candidate_facing;
    u8     adjusted_facing;
    Actor* task;
    Actor* turned_task;
    Actor* panel_task;
    Actor* moving_task;

    if (func_801F5268() & 0xFF) {
        return;
    }
    if (g_Game.flags & GAME_FLAG_SCRIPT_ACTIVE) {
        return;
    }
    if (g_Game.walk_flags & AREA_WALK_ENTRY_PENDING) {
        return;
    }
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        return;
    }
    if (g_Task->unk_0A != 0) {
        return;
    }
    if ((g_Game.input != 0) && !((g_Characters[g_Game.current->character_index].status & STATUS_CONFUSED))) {
        g_Game.current->u.field.step_12A.s8_value = 0;
    }
    if (func_801B6674() & 0xFF) {
        return;
    }
    if (Game_RequestMenuOnInput() & 0xFF) {
        return;
    }
    if (func_801B6258() & 0xFF) {
        return;
    }
    if (func_801F55EC() & 0xFF) {
        return;
    }
    saved_facing = g_Task->direction;
    if ((!(Actor_TurnByPad() & 0xFF) && !(g_InputHeld & g_InputMasks[WORLD_INPUT_RUN])) || (task = g_Task, (task->param.unk_0B == 0x40))) {
        g_Task->direction                         = saved_facing;
        g_Game.current->u.field.mode_12B.s8_value = 0;
        Actor_StopMoving();
        goto block_45;
    }
    if (g_InputHeld & g_InputMasks[WORLD_INPUT_RUN]) {
        task->direction = saved_facing;
    }
    current_facing  = g_Task->direction;
    adjusted_facing = current_facing;
    if (current_facing != saved_facing) {
        facing_delta = (s8)saved_facing - (s8)adjusted_facing;
        if (facing_delta < 0) {
            facing_delta = -facing_delta;
        }
        candidate_facing = saved_facing;
        if (facing_delta >= 3) {
            if ((s8)saved_facing < (s8)adjusted_facing) {
                candidate_facing = saved_facing + 8;
            } else {
                adjusted_facing += 8;
            }
        }
        adjusted_facing_delta = (s8)candidate_facing - (s8)adjusted_facing;
        if (adjusted_facing_delta < 0) {
            adjusted_facing_delta = -adjusted_facing_delta;
        }
        if (adjusted_facing_delta == 2) {
            if ((s8)adjusted_facing < (s8)candidate_facing) {
                g_Task->direction = (u8)(saved_facing - 1);
            } else {
                g_Task->direction = (u8)(saved_facing + 1);
            }
        }
        turned_task            = g_Task;
        turned_task->direction = (u8)(turned_task->direction & 7);
    }
    step_result = func_801B0E44() & 0xFF;
    switch (step_result) { /* irregular */
        case 0x0:
            if ((func_801BDF08() << 0x18) != 0) {
                g_Game.current->u.field.mode_12B.s8_value = 0;
                g_Task->header.step                       = 0;
                func_801F50F4();
                return;
            }
            Area_UpdatePanelRun();
            if ((g_Game.current->u.field.counter_11C.u8_value == 4) && (panel_task = g_Task, (panel_task->direction != saved_facing))) {
                panel_task->direction                     = saved_facing;
                g_Game.current->u.field.mode_12B.s8_value = 0;
            block_46:
                g_Task->header.step = 0;
            } else {
                func_801C24D0();
                func_801C4C48();
                moving_task        = g_Task;
                moving_task->timer = (u8)(moving_task->timer - 1);
                func_801B0DFC();
                g_Game.current->u.field.mode_12B.s8_value = 1;
                g_Task->header.step                       = 1;
                return;
            }
            break;
        case 0x1:
        case 0xFF:
            g_Task->direction                            = saved_facing;
            g_Game.current->u.field.mode_12B.s8_value    = 0;
            g_Game.current->u.field.counter_11C.u8_value = 3U;
        block_45:
            g_Task->timer = 0U;
            goto block_46;
    }
}
#else
INCLUDE_ASM(func_801F4B4C);
#endif
