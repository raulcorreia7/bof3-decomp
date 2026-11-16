#include "area082_13.h"

/* Advances the area fade: the blend colour and shade follow the timer, the
 * three offset bytes take the scroll nudge, and the step ends after 0x5B frames. */
MATCH void func_801F4DC8(void) {
    Actor* colorCell;
    Actor* shadeCell;
    Actor* offsetCell;
    Actor* incCell;
    Actor* gateCell;
    Actor* resetCell;
    s32    level;
    s32    offset;
    u32    color;

    colorCell  = g_Task;
    level      = colorCell->timer;
    color      = (u32)1 << 28 | ((u32)(0x1F - level * 27 / 100) << 10) | ((u32)(0x19 - level * 27 / 100) << 5) | (u32)(u8)((u32)level / 17);
    D_8014933A = 0;
    Area_DrawGradient((s32)color);
    shadeCell = g_Task;
    func_801F5388(0x80 - (u8)((u32)shadeCell->timer / 3));
    offsetCell               = g_Task;
    offset                   = -(s32)offsetCell->timer / 3;
    g_Game.members[0].unk_5F = offset;
    g_Game.members[0].unk_5E = offset;
    g_Game.members[0].unk_5D = offset;
    incCell                  = g_Task;
    incCell->timer++;
    gateCell = g_Task;
    if (gateCell->timer >= 0x5B) {
        gateCell->timer = 0;
        resetCell       = g_Task;
        resetCell->header.step++;
    }
}
