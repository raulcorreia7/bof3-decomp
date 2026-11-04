#include "area008_13.h"

MATCH void func_801F33F0(void) {
    Actor* s;
    Actor* e;
    u8*    flag;
    u8     step;

    s          = g_SpadWork;
    flag       = &g_ScriptVars[3];
    step       = *flag;
    e          = &g_Actors[((u8*)s)[0x0B]];
    g_SpadWork = (Actor*)e;
    if ((step & 0x80u) != 0u) {
        s->unk_01 = 0x0E;
    } else if (g_ScriptVars[1] == 1) {
        u8 next = (u8)(step + 1);

        g_ScriptVars[1] = 2;
        *flag           = next;
        SND_PlayCue(EMI_CUE_ID(2, 13));
        if (((Actor*)g_SpadWork)->script_pc < 5u) {
            D_80146876[0] = 0xFF;
        }
        Actor_SelectScript(2);
        s->unk_01 = 7;
    } else if (e->script_pc == 8 && e->unk_4A == 1) {
        Actor_SelectScript(4);
        s->unk_01 = 4;
    }
    g_SpadWork = s;
}
