#include "area030_04.h"

/* Advances the accessory panel's step cursor through the
 * D_801E20CC entry table, reserves a scenario row for the selected ability,
 * moves the panel by the step deltas and redraws its counter. */
MATCH void func_801D6F34(void) {
    u8 steps;
    u8 slot;
    s8 direction;

    steps = FISHING_STATE->step_timer_09;
    if (steps == 0) {
        if (D_801E20CC[FISHING_STATE->step_index_0A].anim_id == -1) {
            FISHING_STATE->step_index_0A  = D_801E20CC[FISHING_STATE->step_index_0A].next_step;
            FISHING_STATE->saved_index_0B = 0x37;
            FISHING_STATE->pos_x_0C       = 0x6A;
            FISHING_STATE->cursor_10      = 0x6A;
        }
        Actor_RequestScript(D_801E20CC[FISHING_STATE->step_index_0A].anim_id & 0x7F);
        if ((D_801E20CC[FISHING_STATE->step_index_0A].anim_id & 0x7F) == 9) {
            slot = Actor_FindFreeSlot();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0x1A;
                g_SpawnedActors[slot].header.mode  = 0x10;
                g_SpawnedActors[slot].header.step  = 2;
                g_SpawnedActors[slot].unk_03       = 2;
                g_SpawnedActors[slot].unk_2E       = 0xF2;
                g_SpawnedActors[slot].unk_30       = 0x9E;
            }
        }
        FISHING_STATE->step_timer_09 = D_801E20CC[FISHING_STATE->step_index_0A].next_step;
        FISHING_STATE->step_index_0A = FISHING_STATE->step_index_0A + 1;
    } else {
        FISHING_STATE->step_timer_09 = steps - 1;
        if (!(D_801E20CC[FISHING_STATE->step_index_0A - 1].anim_id & 0x80)) {
            Actor_StepAnimLoop();
        }
    }
    FISHING_STATE->pos_x_0C += D_801E20CC[FISHING_STATE->step_index_0A - 1].delta_x;
    FISHING_STATE->cursor_10 += D_801E20CC[FISHING_STATE->step_index_0A - 1].delta_y;
    FISHING_STATE->cue_index_06 -= D_801E20CC[FISHING_STATE->step_index_0A - 1].delta_x;
    direction = 1;
    if (D_801E20CC[FISHING_STATE->step_index_0A - 1].delta_y < 0) {
        /* FAKE: keeps GCC from turning the flag into sge (nor/srl); 7 pure-C spellings stayed at 96.24%. */
        FAKE_BARRIER();
        direction = 0;
    }
    func_801D6B28(direction);
    if (!(g_FrameCount & 0xF)) {
        if (D_801E20CC[FISHING_STATE->step_index_0A - 1].delta_y > 0) {
            FISHING_STATE->saved_index_0B = FISHING_STATE->saved_index_0B + 1;
            if (FISHING_STATE->saved_index_0B >= 0x3D) {
                FISHING_STATE->saved_index_0B = 0x3C;
            }
        }
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, FISHING_STATE->saved_index_0B);
    if (g_FrameCount & 0x4) {
        UI_DrawAsciiString(172, 176, 2, g_UiFormatBuffer);
    } else {
        UI_DrawAsciiString(172, 176, 0, g_UiFormatBuffer);
    }
}
