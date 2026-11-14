#include "area030_04.h"

/* One palette row of D_801E1E80 spans this many bytes. */
#define FISHING_PALETTE_ROW_STRIDE 0xC
/* A palette colour entry spans this many bytes in D_801E1F14 and D_801E1F16. */
#define FISHING_COLOR_ENTRY_SIZE   3
/* The queue table g_FishingPromptSets holds this many column slots per row. */
#define FISHING_QUEUE_COLUMN_COUNT 3
/* The palette entry is drawn this many pixels wide. */
#define FISHING_PALETTE_WIDTH      8
/* The entry animation runs this many steps. */
#define FISHING_EXPAND_STEP_COUNT  4
/* Each entry-animation step narrows the palette entry by this many pixels. */
#define FISHING_EXPAND_STEP_STRIDE 2

/* Slides the area-030 shop text: advances the entry animation, queues the next palette entry into the world
 * record table, and redraws the row highlight and the fill bar. */
MATCH void func_801D3C74(void) {
    s32           color_offset;
    s32           color_index;
    s8            entry;
    u8            count;
    u8            anim_count;
    u8            queue_pos;
    u8            color;
    FishingState* palette;
    FishingState* queue;
    FishingState* draw;
    FishingState* flag;
    FishingState* work;
    FishingState* anim;
    FishingState* timer;

    work              = FISHING_STATE;
    count             = work->step_index_0A;
    work->origin_x_2E = (work->origin_x_2E - 2);
    if (count != 0) {
        work->step_index_0A = (count - 1);
        anim                = FISHING_STATE;
        anim_count          = anim->step_index_0A;
        color_offset        = *(D_801E1E80 + (anim->row_4B * FISHING_PALETTE_ROW_STRIDE)) * FISHING_COLOR_ENTRY_SIZE;
        func_801D9740(*(D_801E1F16 + color_offset), color_offset + D_801E1F14, (FISHING_PALETTE_WIDTH - (anim_count * FISHING_EXPAND_STEP_STRIDE)) & BYTE_MASK,
                      0x125 - ((FISHING_EXPAND_STEP_COUNT - anim_count) * FISHING_EXPAND_STEP_STRIDE));
    } else {
        work->step_timer_09 = (work->step_timer_09 - 1);
        timer               = FISHING_STATE;
        if (timer->step_timer_09 == 0) {
            timer->column_4A = (timer->column_4A + 1);
            queue            = FISHING_STATE;
            queue_pos        = queue->column_4A;
            if ((queue_pos >= FISHING_QUEUE_COLUMN_COUNT) || (g_FishingPromptSets[queue->cue_index_06][queue_pos] == GAME_NONE)) {
                queue->column_4A = 0U;
            }
            if (D_80144125 != 7) {
                entry = Actor_FindFreeSlot();
                if (entry != -1) {
                    g_SpawnedActors[entry].header.flags = 1;
                    g_SpawnedActors[entry].type         = 0xF;
                    g_SpawnedActors[entry].header.mode  = 8;
                    g_SpawnedActors[entry].unk_06       = FISHING_STATE->cue_index_06;
                    g_SpawnedActors[entry].unk_4A       = FISHING_STATE->column_4A;
                    g_SpawnedActors[entry].link         = 0;
                }
            }
            flag                   = FISHING_STATE;
            flag->handler_index_01 = (flag->handler_index_01 + 1);
        }
        palette = FISHING_STATE;
        color   = *(D_801E1E80 + (palette->row_4B * FISHING_PALETTE_ROW_STRIDE));
        if (color != GAME_NONE) {
            color_index = color * FISHING_COLOR_ENTRY_SIZE;
            UI_DrawText((palette->origin_x_2E + (palette->counter_49 * FISHING_PALETTE_WIDTH)), (D_80144154 + 2), *(D_801E1F16 + color_index), 1U, (color_index + D_801E1F14));
        }
    }
    draw = FISHING_STATE;
    UI_DrawText(draw->origin_x_2E, (D_80144154 + 2), 0, draw->counter_49, draw->item_50.pointer);
}
