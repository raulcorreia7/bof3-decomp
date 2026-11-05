/* Every step re-reads the scratchpad cell. */
#define SPAD_WORK_VOLATILE
#include "magic102_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

/* Counts this effect's steps; at the tick limit it re-arms the counter, steps
 * the magic, and flips the area camera's vertical offset with the frame parity. */
MATCH void func_801EF218(void) {
    PartyBattler* work;
    u8            tick;

    work                      = g_SpadWork;
    tick                      = work->word_08.byte.unk_09 + EFFECT_TICK_INCREMENT;
    work->word_08.byte.unk_09 = tick;
    if (tick >= EFFECT_TICK_LIMIT) {
        g_SpadWork->word_08.byte.unk_09 = 0;
        g_SpadWork->step_01 += 1;
    }
    g_AreaCameraOffsetY      = (((g_FrameCount & 1) * 2) - 1) * (g_SpadWork->word_08.byte.unk_09 >> 1);
    g_AreaCameraRefreshCount = 2;
}

INCLUDE_ASM(func_801EF2B8);

INCLUDE_ASM(func_801EFD7C);

INCLUDE_ASM(func_801EFEFC);

/* Template: exe Area_DrawGouraudQuads needs the local i, which this function lacks; compile fails. */
INCLUDE_ASM(func_801F016C);

INCLUDE_ASM(func_801F0488);

INCLUDE_ASM(func_801F0778);

INCLUDE_ASM(func_801F0ADC);
