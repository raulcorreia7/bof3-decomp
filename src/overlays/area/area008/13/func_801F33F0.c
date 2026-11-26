#include "area008_13.h"

MATCH void func_801F33F0(void) {
    Actor* s;
    Actor* e;
    u8*    flag;
    u8     step;

    s    = SELF(Actor);
    flag = &g_ScriptVars[3];
    step = *flag;
    e    = &g_Actors[s->param.unk_0B];
    SELF_SET(e);
    if ((step & 0x80u) != 0u) {
        s->header.mode = 0x0E;
    } else if (g_ScriptVars[1] == 1) {
        u8 next = (step + 1);

        g_ScriptVars[1] = 2;
        *flag           = next;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 13));
        if (SELF(Actor)->script_pc < 5u) {
            D_80146876[0] = 0xFF;
        }
        Script_Select(2);
        s->header.mode = 7;
    } else if (e->script_pc == 8 && e->unk_4A == 1) {
        Script_Select(4);
        s->header.mode = 4;
    }
    g_Self = s;
}
