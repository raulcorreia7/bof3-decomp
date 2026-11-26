#include "area030_04.h"

/* Advances the accessory panel's step cursor through the
 * D_801E20CC entry table, reserves a scenario row for the selected ability,
 * moves the panel by the step deltas and redraws its counter. */
MATCH void func_801D6F34(void) {
    u8 steps;
    u8 slot;
    s8 direction;

    steps = SELF(FishingState)->timer;
    if (steps == 0) {
        if (D_801E20CC[SELF(FishingState)->step_index].animation_id == -1) {
            SELF(FishingState)->step_index  = D_801E20CC[SELF(FishingState)->step_index].next_step;
            SELF(FishingState)->saved_index = 0x37;
            SELF(FishingState)->pos_x       = 0x6A;
            SELF(FishingState)->cursor_10   = 0x6A;
        }
        Script_Request(D_801E20CC[SELF(FishingState)->step_index].animation_id & 0x7F);
        if ((D_801E20CC[SELF(FishingState)->step_index].animation_id & 0x7F) == 9) {
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0x1A;
                g_SpawnedActors[slot].header.mode  = 0x10;
                g_SpawnedActors[slot].header.step  = 2;
                g_SpawnedActors[slot].unk_03       = 2;
                g_SpawnedActors[slot].screen_x     = 0xF2;
                g_SpawnedActors[slot].screen_y     = 0x9E;
            }
        }
        SELF(FishingState)->timer      = D_801E20CC[SELF(FishingState)->step_index].next_step;
        SELF(FishingState)->step_index = SELF(FishingState)->step_index + 1;
    } else {
        SELF(FishingState)->timer = steps - 1;
        if (!(D_801E20CC[SELF(FishingState)->step_index - 1].animation_id & 0x80)) {
            Script_AnimStepLoop();
        }
    }
    SELF(FishingState)->pos_x += D_801E20CC[SELF(FishingState)->step_index - 1].delta_x;
    SELF(FishingState)->cursor_10 += D_801E20CC[SELF(FishingState)->step_index - 1].delta_y;
    SELF(FishingState)->cue_index -= D_801E20CC[SELF(FishingState)->step_index - 1].delta_x;
    direction = 1;
    if (D_801E20CC[SELF(FishingState)->step_index - 1].delta_y < 0) {
        /* FAKE: keeps GCC from turning the flag into sge (nor/srl); 7 pure-C spellings stayed at 96.24%. */
        FAKE_BARRIER();
        direction = 0;
    }
    func_801D6B28(direction);
    if (!(g_FrameCount & 0xF)) {
        if (D_801E20CC[SELF(FishingState)->step_index - 1].delta_y > 0) {
            SELF(FishingState)->saved_index = SELF(FishingState)->saved_index + 1;
            if (SELF(FishingState)->saved_index >= 0x3D) {
                SELF(FishingState)->saved_index = 0x3C;
            }
        }
    }
    TEXT_Format(g_UiTextFormatBuffer, D_801D0C04, SELF(FishingState)->saved_index);
    if (g_FrameCount & 0x4) {
        UI_TextDrawAscii(172, 176, UI_TEXT_HIGHLIGHT, g_UiTextFormatBuffer);
    } else {
        UI_TextDrawAscii(172, 176, 0, g_UiTextFormatBuffer);
    }
}
