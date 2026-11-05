#include "area030_04.h"

/* Draws the area-030 party bars: the actor's own bar row, the
 * member bars and the name text. */
/* nonmatching unmeasured: the bar count is 10 with a live step index and 9 without it (the retail sets s3 to 10 and
 * 9 on the two paths) and the slot stores run flags, type, unk_01, unk_02; candidate 68.92%. resume: a source
 * shape that homes the work pointer in a0 like the retail. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D72E4(s16 panel_x, s16 panel_y) {
    u16 value;
    u16 health;
    u8  bar_index;
    u8  bar_count;
    u8  bar_slot;
    s16 bar_y;
    s16 bar_x;
    s32 count;
    s32 health_step;
    s32 member;
    u8* text;
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);

    UI_DrawWindow(panel_x & HALF_MASK, panel_y & HALF_MASK, 0xF2, 0x9F, 0xF0, (s32)D_80144952);
    if (FISHING_STATE->counter_08 != 0) {
        if (FISHING_STATE->step_timer_09 == 0) {
            health = FISHING_STATE->bounce_3C.half.unk_3C;
            if (FISHING_STATE->bounce_3C.half.key_3E != health) {
                FISHING_STATE->step_limit_20         = (s32)(health * 9);
                FISHING_STATE->bounce_3C.half.key_3E = (s16)FISHING_STATE->bounce_3C.half.unk_3C;
            }
            if ((s8)FISHING_STATE->counter_08 > 0) {
                health_step            = FISHING_STATE->step_14 - 1;
                FISHING_STATE->step_14 = health_step;
                if (health_step < 0) {
                    FISHING_STATE->step_14 = 0x35;
                }
            }
            FISHING_STATE->step_timer_09 = (u8)(FISHING_STATE->step_timer_09 + 1);
            FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
        }
        if (FISHING_STATE->step_index_0A == 0) {
            health_step = FISHING_STATE->step_14;
            if (health_step == FISHING_STATE->step_limit_20) {
                FISHING_STATE->step_timer_09      = 0U;
                FISHING_STATE->counter_08         = 0U;
                member                            = Actor_FindFreeSlot() & BYTE_MASK;
                g_ActorSlots[member].flags        = 1;
                g_ActorSlots[member].type         = 0x1A;
                g_ActorSlots[member].mode         = 0x10;
                *(s16*)&g_ActorSlots[member].step = (s16)FISHING_STATE->bounce_3C.half.key_3E;
            } else {
                health_step = health_step - 1;
                if ((s8)FISHING_STATE->counter_08 > 0) {
                    FISHING_STATE->step_14 = health_step;
                    if (health_step < 0) {
                        FISHING_STATE->step_14 = 0x35;
                    }
                }
                FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
            }
        } else {
            FISHING_STATE->step_index_0A = (u8)(FISHING_STATE->step_index_0A + 1);
            if (FISHING_STATE->step_index_0A == 4) {
                FISHING_STATE->step_index_0A = 0U;
                if ((s8)FISHING_STATE->counter_08 < 0) {
                    health_step            = FISHING_STATE->step_14 + 1;
                    FISHING_STATE->step_14 = health_step;
                    if (health_step >= 0x36) {
                        FISHING_STATE->step_14 = 0;
                    }
                }
            }
        }
    }
    bar_slot = (u8)FISHING_STATE->step_index_0A;
    bar_y    = panel_y + 0x19;
    if (bar_slot != 0) {
        if (FISHING_STATE->counter_08 == 1) {
            bar_y = (s16)(panel_y + ((bar_slot * 3) + 0xC));
        } else {
            bar_y = (s16)(panel_y - ((bar_slot * 3) - 0x19));
        }
        bar_count = 10;
    } else {
        bar_count = 9;
    }
    bar_index = (u8)FISHING_STATE->step_14;
    count     = 0;
    if (bar_count != 0) {
        bar_x = (s16)(panel_x + 6);
        do {
            value = D_801E2120[bar_index & BYTE_MASK];
            if (value != 0xFFFF) {
                UI_DrawText(bar_x, bar_y, 0, 0xFFU, ((u8*)&D_80010000 + D_80010000[value]));
            }
            bar_index += 1;
            if ((u32)(bar_index & BYTE_MASK) >= 0x36U) {
                bar_index = 0;
            }
            count += 1;
            bar_y += 0xD;
        } while (count < bar_count);
    }
    UI_DrawWindow(panel_x & HALF_MASK, (panel_y + 6) & HALF_MASK, 0xF2, 0xE, 0, (s32)D_80144952);
    UI_DrawWindow(panel_x & HALF_MASK, (panel_y + 0x94) & HALF_MASK, 0xF2, 0xB, 0x30, (s32)D_80144952);
    health = FISHING_STATE->bounce_3C.half.unk_3C;
    UI_DrawText((s16)(panel_x + 0x3D), (s16)(panel_y + 6), 0, 0xFFU,
                ((u8*)&D_80010000 + D_80010000[D_801E2114[health]]));
    func_801D7784((u16)panel_x, (u16)panel_y);
    text = (u8*)g_UiFormatBuffer;
    sprintf((s8*)text, &D_801D0C08, health + 1);
    UI_DrawGlyphString((s16)(panel_x + 0xCA), (s16)(panel_y + 0x92), 0U, text);
}
#else
INCLUDE_ASM(func_801D72E4);
#endif
